#include <glew.h>
#include "stb_image/stb_image.h"

#include <iostream>

#include "standardObject.h"
#include "generatePrimitives.h"
#include "initit.h"
#include "input.h"

standardObject::standardObject(float x_position, float y_position, mootor* mootor, bool isTextured)
	:objectPosition{ x_position, y_position }, textured(isTextured), amountDrawn(0), motor(mootor)
{
	glGenVertexArrays(1, &VArray);
	glGenBuffers(1, &VBuffer);
	glGenBuffers(1, &EBuffer);

	std::cout << "object created" << std::endl;
}

standardObject::~standardObject()
{
	delete[] vertexBuffer;
	delete[] elementBuffer;
	std::cout << "memory freed?" << std::endl;
}

void standardObject::addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size, bool deletePreviousBuffers = false)
{
	if (deletePreviousBuffers)
	{
		glDeleteVertexArrays(1, &VArray);
		glDeleteBuffers(1, &VBuffer);
		glDeleteBuffers(1, &EBuffer);

		glGenVertexArrays(1, &VArray);
		glGenBuffers(1, &VBuffer);
		glGenBuffers(1, &EBuffer);
	}

	glBindVertexArray(VArray);
	glBindBuffer(GL_ARRAY_BUFFER, VBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertecies_Size, vertecies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_Size, indicies, GL_STATIC_DRAW);
	amountDrawn = indicies_Size / sizeof(unsigned int);
	std::cout << vertecies_Size << " " << indicies_Size << " " << amountDrawn << std::endl;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void standardObject::addTexture(const char* filepath, int texmap_width, int texmap_height, int items_in_map)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
	if (nrChannels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else if (nrChannels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	texmap[0] = texmap_width;
	texmap[1] = texmap_height;
	texmapitems = items_in_map;
}

void standardObject::softSwapTexture(const float& tilemapNum)
{
	int x = vbSize / 6;

	for (int i = 1; i <= x; i++)
	{
		vertexBuffer[i * 6 - 1] = tilemapNum;
	}

	glBindVertexArray(VArray);
	glBindBuffer(GL_ARRAY_BUFFER, VBuffer);
	glBufferData(GL_ARRAY_BUFFER, vbSize * sizeof(float), vertexBuffer, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void standardObject::SetObjectRotation(const float& deg)
{
	objectRotation = deg;

	float angle = objectRotation * 3.14159f / 180.0f;

	*(modelMat) = cos(angle);
	*(modelMat + 1) = -sin(angle);
	*(modelMat + 4) = sin(angle);
	*(modelMat + 5) = cos(angle);
}

void standardObject::RotateObject(const float& deg)
{
	objectRotation += -deg;

	float angle = objectRotation * 3.14159f / 180.0f;

	*(modelMat) = cos(angle);
	*(modelMat + 1) = -sin(angle);
	*(modelMat + 4) = sin(angle);
	*(modelMat + 5) = cos(angle);
}

void standardObject::SetObjectPosition(float* pos)
{
	objectPosition[0] = pos[0];
	objectPosition[1] = pos[1];

	*(modelMat + 3) = objectPosition[0];
	*(modelMat + 7) = objectPosition[1];
}

void standardObject::MoveObject(float* vec)
{
	objectPosition[0] += vec[0];
	objectPosition[1] += vec[1];

	*(modelMat + 3) = objectPosition[0];
	*(modelMat + 7) = objectPosition[1];
}

void standardObject::MakeCircle(float radius, float degreesPerTriangle)
{
	bufferSizeStore bufferSizes = genCircle(textured, vertexBuffer, elementBuffer, degreesPerTriangle, radius, objectPosition[0], objectPosition[1]);
	vbSize = bufferSizes.vertexBufferSize;
	ibSize = bufferSizes.elementBufferSize;
	//dont forget to multiply the size of array(how many elements there are) with the size of the actual variable type in that array
	addData(vertexBuffer, bufferSizes.vertexBufferSize * sizeof(float), elementBuffer, bufferSizes.elementBufferSize * sizeof(unsigned int));
}

void standardObject::MakeTriangle(float width, float height)
{
	bufferSizeStore bufferSizes = genTriangle(textured, vertexBuffer, elementBuffer, width, height, objectPosition[0], objectPosition[1]);
	vbSize = bufferSizes.vertexBufferSize;
	ibSize = bufferSizes.elementBufferSize;
	addData(vertexBuffer, bufferSizes.vertexBufferSize * sizeof(float), elementBuffer, bufferSizes.elementBufferSize * sizeof(unsigned int));
}

void standardObject::MakeSquare(float width, float height)
{
	objectDimensions[0] = width;
	objectDimensions[1] = height;

	bufferSizeStore bufferSizes = genSquare(textured, vertexBuffer, elementBuffer, width, height, objectPosition[0], objectPosition[1]);
	vbSize = bufferSizes.vertexBufferSize;
	ibSize = bufferSizes.elementBufferSize;
	addData(vertexBuffer, bufferSizes.vertexBufferSize * sizeof(float), elementBuffer, bufferSizes.elementBufferSize * sizeof(unsigned int));
}

void standardObject::MakeCustom(float* vertex_buffer, int vbSize, unsigned int* index_buffer, int ibSize)
{
	this->vbSize = vbSize;
	this->ibSize = ibSize;
	addData(vertex_buffer, vbSize, index_buffer, ibSize);
}

void standardObject::Draw(shaderManager& base) const
{
	glBindVertexArray(VArray);

	base.UseProgram();

	int loc = glGetUniformLocation(base.program, "modelMat");
	glUniformMatrix4fv(loc, 1, GL_TRUE, modelMat);

	int uniloc = glGetUniformLocation(base.program, "texmapdims");
	glUniform2iv(uniloc, 1, texmap);

	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawElements(GL_TRIANGLES, amountDrawn, GL_UNSIGNED_INT, 0);
}	

tilemap::tilemap(int tileside_pixels, int tilemap_width, int tilemap_height, float position[2])
{
	glGenVertexArrays(1, &VArray);
	glGenBuffers(1, &VBuffer);
	glGenBuffers(1, &EBuffer);

	bufferSizeStore bufferSizes = genTileMap(tilemap_buffer, index_buffer, tilemap_width, tilemap_height, tileside_pixels, position);
	vbSize = bufferSizes.vertexBufferSize * sizeof(float);
	ibSize = bufferSizes.elementBufferSize * sizeof(unsigned int);
	addData(tilemap_buffer, vbSize, index_buffer, ibSize);

	int magicint = 0;
	for (int i = 0; i < tilemap_height; i++)
	{
		for (int j = 0; j < tilemap_width * 4; j++)
		{
			magicint++;
		}
	}


	std::cout << magicint << " " << ibSize / sizeof(unsigned int) / 6 << '\n';
	system("pause");
}

void tilemap::addTexture(const char* filepath, int texmap_width, int texmap_height, int items_in_map)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
	if (nrChannels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else if (nrChannels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	texmap[0] = texmap_width;
	texmap[1] = texmap_height;
	texmapitems = items_in_map;

	for (auto i : texmap)
	{
		std::cout << i << std::endl;
	}
	//system("pause");
}

void tilemap::addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size)
{
	glBindVertexArray(VArray);
	glBindBuffer(GL_ARRAY_BUFFER, VBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertecies_Size, vertecies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_Size, indicies, GL_STATIC_DRAW);

	amountDrawn = indicies_Size / sizeof(unsigned int);
	std::cout << vertecies_Size << " " << indicies_Size << " " << amountDrawn << std::endl;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void tilemap::Draw(shaderManager& base)
{
	glBindVertexArray(VArray);

	base.UseProgram();

	int uniloc = glGetUniformLocation(base.program, "texmapdims");
	glUniform2iv(uniloc, 1, texmap);

	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawElements(GL_TRIANGLES, amountDrawn, GL_UNSIGNED_INT, 0);
}

tilemap::~tilemap()
{
	delete[] tilemap_buffer;
	delete[] index_buffer;
}

//method is slow, this should only be used during loading processes
//DON'T USE IN APP LOOP, LIKELY TO KILL PERFORMANCE
//
//Compatability with standardObject makeCircle and makeSquare functions is NOT GUARANTEED
void combinedObject::addObject(standardObject* object)
{
	if (vbSize == 0 && ibSize == 0)
	{
		vbSize += object->vbSize;
		ibSize += object->ibSize;

		vertexBuffer = new float[vbSize] {0};
		elementBuffer = new unsigned int[ibSize] {0};

		for (int i = 0; i < vbSize; i++)
		{
			this->vertexBuffer[i] = object->vertexBuffer[i];
		}
		for (int i = 0; i < ibSize; i++)
		{
			this->elementBuffer[i] = object->elementBuffer[i];
		}

		addData(vertexBuffer, vbSize * sizeof(float), elementBuffer, ibSize * sizeof(unsigned int), false);
	}
	else
	{
		std::cout << "combinedObject: " << vbSize << " " << ibSize << " was\n";
		std::cout << "added object " << object->vbSize << " " << object->ibSize << " was\n";
		vbSize += object->vbSize;
		ibSize += object->ibSize;
		std::cout << "combinedObject: " << vbSize << " " << ibSize << " now is\n";
		system("pause");

		float* tempVertBuffer = new float[vbSize] {0};
		unsigned int* tempIndexBuffer = new unsigned int[ibSize] {0};

		//transfer two vertexBuffers to a temporary buffer
		for (int i = 0; i < vbSize - object->vbSize; i++)
		{
			tempVertBuffer[i] = this->vertexBuffer[i];
		}
		for (int i = 0; i < object->vbSize; i++)
		{
			tempVertBuffer[(vbSize - object->vbSize) + i] = object->vertexBuffer[i];
		}

		//transfer two indexBuffers to a temporary buffer
		//here we must also modify the added indexes to prevent breaking things
		for (int i = 0; i < ibSize - object->ibSize; i++)
		{
			tempIndexBuffer[i] = this->elementBuffer[i];
		}
		for (int i = ibSize - object->ibSize; i < ibSize; i++)
		{
			//THIS IS NOT A SAFE SOLUTION
			// we are currently doing offset(combinedObj previous vbSize / 6 (mis on ühe punkti suurus floatides)) + indexValue (from the object index buffer)
			tempIndexBuffer[i] = (vbSize - object->vbSize) / 6 + object->elementBuffer[i - (ibSize - object->ibSize)];
		}

		//null the main buffers and transfer back the contents from the temp pointers
		delete[] this->vertexBuffer;
		delete[] this->elementBuffer;
		this->vertexBuffer = new float[vbSize] {0};
		this->elementBuffer = new unsigned int[ibSize] {0};

		for (int i = 0; i < vbSize; i++)
		{
			this->vertexBuffer[i] = tempVertBuffer[i];
		}
		for (int i = 0; i < ibSize; i++)
		{
			this->elementBuffer[i] = tempIndexBuffer[i];
		}

		//call to addData to make things work things hopefully
		addData(vertexBuffer, vbSize * sizeof(float), elementBuffer, ibSize * sizeof(unsigned int), true);

		//free memory of the temp pointers
		delete[] tempVertBuffer;
		delete[] tempIndexBuffer;

		//debug stuff
		for (int i = 0; i < vbSize; i++)
		{
			std::cout << this->vertexBuffer[i] << " ";
			if ((i + 1) % 6 == 0)
			{
				std::cout << std::endl;
			}
		}
		std::cout << "\n";
		for (int i = 0; i < ibSize; i++)
		{
			std::cout << this->elementBuffer[i] << " ";
			if ((i + 1) % 3 == 0)
			{
				std::cout << std::endl;
			}
		}
	}

	std::cout << vbSize << " " << ibSize << " <- vertexBufferSize and indexBufferSize!" << std::endl;
	system("pause");
}

void combinedObject::addObjectList(standardObject** objectPointer, const unsigned int& numberOfObjects)
{
	for (int i = 0; i < numberOfObjects; i++)
	{
		addObject(objectPointer[i]);
	}
}

void buttonObject::setOnClick(void(*func)(buttonObject*))
{
	OnClick = func;
}

bool buttonObject::checkClick(bool centerMouseCords)
{
	position mouse = TMouse::GetMousePos(this->motor->window);
	float x[2] = { this->objectPosition[0] - this->objectDimensions[0] / 2 - this->motor->GetGlobalPosition()[0], this->objectPosition[0] + this->objectDimensions[0] / 2 - this->motor->GetGlobalPosition()[0]};
	float y[2] = { this->objectPosition[1] - this->objectDimensions[1] / 2- this->motor->GetGlobalPosition()[1], this->objectPosition[1] + this->objectDimensions[1] / 2 - this->motor->GetGlobalPosition()[1]};

	if (centerMouseCords)
	{
		mouse.xPos = mouse.xPos - this->motor->GetWindowDimensions()[0] / 2;
		mouse.yPos = mouse.yPos - this->motor->GetWindowDimensions()[1] / 2;

		const bool flipMouseY = true;
		if (flipMouseY)
		{
			mouse.yPos = mouse.yPos * -1;
		}
	}

	std::cout << x[0] << " " << mouse.xPos << " " << x[1] << std::endl;
	std::cout << y[0] << " " << mouse.yPos << " " << y[1] << std::endl;

	if (x[0] < float(mouse.xPos) && float(mouse.xPos) < x[1] &&
		y[0] < float(mouse.yPos) && float(mouse.yPos) < y[1])
	{
		if (TMouse::isButtonPressed(this->motor->window, GLFW_MOUSE_BUTTON_LEFT))
		{
			return true;
		}
	}
	return false;
}

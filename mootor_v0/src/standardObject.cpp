#include <glew.h>
#include "stb_image/stb_image.h"

#include <iostream>

#include "standardObject.h"
#include "generatePrimitives.h"
#include "initit.h"

standardObject::standardObject(float x_position, float y_position, mootor* mootor, bool isTextured)
	:originPosition{ x_position, y_position }, textured(isTextured), amountDrawn(0), motor(mootor)
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

void standardObject::addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size)
{
	glBindVertexArray(VArray);
	glBindBuffer(GL_ARRAY_BUFFER, VBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertecies_Size, vertecies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_Size, indicies, GL_STATIC_DRAW);
	amountDrawn = indicies_Size / sizeof(unsigned int);
	std::cout << vertecies_Size << " " << indicies_Size << " " << amountDrawn << std::endl;

	if (!textured)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	} 
	else
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void standardObject::addTexture(const char* filepath)
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
}

void standardObject::MakeCircle(float radius, float degreesPerTriangle)
{
	bufferSizeStore bufferSizes = genCircle(textured, vertexBuffer, elementBuffer, degreesPerTriangle, radius, originPosition[0], originPosition[1]);
	//dont forget to multiply the size of array(how many elements there are) with the size of the actual variable type in that array
	addData(vertexBuffer, bufferSizes.vertexBufferSize * sizeof(float), elementBuffer, bufferSizes.elementBufferSize * sizeof(unsigned int));
}

void standardObject::MakeSquare(float width, float height)
{
	bufferSizeStore bufferSizes = genSquare(textured, vertexBuffer, elementBuffer, width, height, originPosition[0], originPosition[1]);
	addData(vertexBuffer, bufferSizes.vertexBufferSize * sizeof(float), elementBuffer, bufferSizes.elementBufferSize * sizeof(unsigned int));
}

void standardObject::Draw() const
{
	glBindVertexArray(VArray);

	if (textured)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	glDrawElements(GL_TRIANGLES, amountDrawn, GL_UNSIGNED_INT, 0);
}	

void buttonObject::refreshMousePosition()
{

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
	system("pause");
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

	int uniloc = glGetUniformLocation(base.program, "texmapdims");
	glUniform2iv(uniloc, 1, texmap);

	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawElements(GL_TRIANGLES, amountDrawn, GL_UNSIGNED_INT, 0);
	//glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 4);

	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 1);

	//glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 4);
}

tilemap::~tilemap()
{
	delete[] tilemap_buffer;
	delete[] index_buffer;
}

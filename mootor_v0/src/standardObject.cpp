#include <glew.h>
#include "stb_image/stb_image.h"

#include <iostream>

#include "standardObject.h"
#include "generatePrimitives.h"

standardObject::standardObject(float x_position, float y_position, bool isTextured)
	:originPosition{ x_position, y_position }, textured(isTextured), amountDrawn(0)
{
	glGenVertexArrays(1, &VArray);
	glGenBuffers(1, &VBuffer);
	glGenBuffers(1, &EBuffer);
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

void standardObject::addTexture()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("C:/dev_kaust/mootor_v0/mootor_v0/src/textures/test.jpg", &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void standardObject::MakeCircle(float radius, float degreesPerTriangle)
{
	if (!textured)
	{
		bufferSizeStore bufferSizes = genCircle(textured, vertexBuffer, elementBuffer, degreesPerTriangle, radius, originPosition[0], originPosition[1]);
		//dont forget to multiply the size of array(how many elements there are) with the size of the actual variable type in that array
		addData(vertexBuffer, bufferSizes.vertexBufferSize * sizeof(float), elementBuffer, bufferSizes.elementBufferSize * sizeof(unsigned int));
	}
	else
	{
		bufferSizeStore bufferSizes = genCircle(textured, vertexBuffer, elementBuffer, degreesPerTriangle, radius, originPosition[0], originPosition[1]);
		//dont forget to multiply the size of array(how many elements there are) with the size of the actual variable type in that array
		addData(vertexBuffer, bufferSizes.vertexBufferSize * sizeof(float), elementBuffer, bufferSizes.elementBufferSize * sizeof(unsigned int));
	}
}

void standardObject::MakeSquare(float width, float height)
{
	if (!textured)
	{
		vertexBuffer = new float[12] {0};
		elementBuffer = new unsigned int[6] {0}; //vbuffersize -3 since we make one triangle per point generated except the middle of the circle
		genSquare(vertexBuffer, elementBuffer, width, height, originPosition[0], originPosition[1]);
		//dont forget to multiply the size of array(how many elements there are) with the size of the actual variable type in that array
		addData(vertexBuffer, 12 * sizeof(float), elementBuffer, 6 * sizeof(unsigned int));
	}
	else 
	{

	}
}

void standardObject::Draw() const
{
	//bindime ajutiselt shaderid siin kuni ma mingi parema asja valja motlen
	//aga seda siis kui me sinna jouame
	if (!textured)
	{
		glBindVertexArray(VArray);
		glDrawElements(GL_TRIANGLES, amountDrawn, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glBindVertexArray(VArray);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawElements(GL_TRIANGLES, amountDrawn, GL_UNSIGNED_INT, 0);
	}
}
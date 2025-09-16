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
	if (!textured)
	{
		glBindVertexArray(VArray);
		glBindBuffer(GL_ARRAY_BUFFER, VBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertecies_Size, vertecies, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_Size, indicies, GL_STATIC_DRAW);
		amountDrawn = indicies_Size / sizeof(unsigned int);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	} 
	else
	{
		//set it up as textured
	}
}

void standardObject::MakeCircle(float radius, float degreesPerTriangle)
{
	if (!textured)
	{
		//int vBufferSize = calcCircleVBufferSize(degreesPerTriangle);
		//vertexBuffer = new float[vBufferSize] {0};
		//elementBuffer = new unsigned int[vBufferSize - 3] {0}; //vbuffersize -3 since we make one triangle per point generated except the middle of the circle
		bufferSizeStore bufferSizes = genCircle(vertexBuffer, elementBuffer, degreesPerTriangle, radius, originPosition[0], originPosition[1]);
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

	}
}
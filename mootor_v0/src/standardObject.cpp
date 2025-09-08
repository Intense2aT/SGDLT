#include <glew.h>
#include <iostream>

#include "standardObject.h"

standardObject::standardObject()
	:amountDrawn(0)
{
	glGenVertexArrays(1, &VArray);
	glGenBuffers(1, &VBuffer);
	glGenBuffers(1, &EBuffer);
}

standardObject::~standardObject()
{

}

void standardObject::addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size)
{
	glBindVertexArray(VArray);
	glBindBuffer(GL_ARRAY_BUFFER, VBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertecies_Size, vertecies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_Size, indicies, GL_STATIC_DRAW);
	amountDrawn = indicies_Size / sizeof(unsigned int);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void standardObject::Draw()
{
	glBindVertexArray(VArray);
	glDrawElements(GL_TRIANGLES, amountDrawn, GL_UNSIGNED_INT , 0);
}

/*
void standardObject::BindObject()
{
	glBindVertexArray(VArray);
}
*/
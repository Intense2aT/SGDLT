#include <glew.h>
#include <iostream>

#include "standardObject.h"

standardObject::standardObject(bool isTextured)
	:amountDrawn(0), textured(isTextured)
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

		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	} 
	else
	{
		//set it up as textured
	}
}

void standardObject::Draw()
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

/*
void standardObject::BindObject()
{
	glBindVertexArray(VArray);
}
*/
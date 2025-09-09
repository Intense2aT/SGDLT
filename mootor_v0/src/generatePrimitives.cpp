#include <iostream>
#include <math.h>

#include "generatePrimitives.h"

//always returns an array with 12 floats to targetArray 4 * {x, y, z}
//index array passed to the function should always have a 6 uint allocation
void genSquare(float* vertexArray, unsigned int* indexArray, float width, float height, float xpos, float ypos)
{
	float* Square = new float[12];
	for (int i = 1; i < 5; i++)
	{
		Square[3 * i - 1] = 1.0f;
	}

	//float corners[4][2] = { {0.0f, height},{0.0f, 0.0f},{width, 0.0f},{width, height} };

	//triangles
	Square[0] = xpos + 0.0f;
	Square[1] = ypos + height;

	Square[3] = xpos + 0.0f;
	Square[4] = ypos + 0.0f;

	Square[6] = xpos + width;
	Square[7] = ypos + 0.0f;

	Square[9] = xpos + width;
	Square[10] = ypos + height;

	for (int i = 0; i < 12; i++)
	{
		*(vertexArray + i) = Square[i];
		//std::cout << vertexArray[i] << std::endl;
	}

	*indexArray = 0;
	*(indexArray + 1) = 1;
	*(indexArray + 2) = 2;
	*(indexArray + 3) = 2;
	*(indexArray + 4) = 3;
	*(indexArray + 5) = 0;

	delete[] Square;
}

int calcCircleVBufferSize(float degreesPerTriangle)
{
	return (int)(360 / degreesPerTriangle + 1) * 3;
}

//target array should equal 3*output of calcTriangleCount() in order to fit x, y and z
void genCircle(float* vertexArray, unsigned int* indexArray, float triangleDegrees, float radius, float xpos, float ypos)
{
	int triangles = (int)(360 / triangleDegrees);
	float angle = 3.1415f * 2.0f / triangles; //calculating radians
	//currently need to write 1 point per loop

	vertexArray[0] = xpos;
	vertexArray[1] = ypos;
	vertexArray[2] = 1.0f;

	for (int i = 1; i < triangles + 1; i++)
	{
		float nextAngle = angle * i; 
		vertexArray[3 * i] = xpos + radius * sin(nextAngle);
		vertexArray[3 * i + 1] = ypos + radius * cos(nextAngle);
		vertexArray[3 * i + 2] = 1.0f;

		indexArray[3 * (i - 1)] = 0;
		indexArray[3 * (i - 1) + 1] = i;
		indexArray[3 * (i - 1) + 2] = (i + 1 > triangles) ? 1 : i + 1;
	}

	/*
	for (int i = 1; i < vBufferSize + 1; i++)
	{
		std::cout << *(testArray3 + i - 1) << " ";
		if (i % 3 == 0)
		{
			std::cout << std::endl;
		}
	}

	for (int i = 1; i < vBufferSize - 2; i++)
	{
		std::cout << *(testArray4 + i - 1) << " ";
		if (i % 3 == 0)
		{
			std::cout << std::endl;
		}
	}
	*/
}
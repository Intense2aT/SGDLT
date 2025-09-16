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
bufferSizeStore genCircle(bool generateTextured, float*& vertexArray, unsigned int*& indexArray, float triangleDegrees, float radius, float xpos, float ypos)
{
	bufferSizeStore bufferSizes;
	bufferSizes.elementBufferSize = calcCircleVBufferSize(triangleDegrees) - 3;

	if (!generateTextured)
	{
		bufferSizes.vertexBufferSize = bufferSizes.elementBufferSize + 3;

		vertexArray = new float[bufferSizes.vertexBufferSize] {0};
		indexArray = new unsigned int[bufferSizes.elementBufferSize] {0};

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
	}
	else
	{
		bufferSizes.vertexBufferSize = (bufferSizes.elementBufferSize + 3) / 3 * 5;

		vertexArray = new float[bufferSizes.vertexBufferSize] {0};
		indexArray = new unsigned int[bufferSizes.elementBufferSize] {0};

		int triangles = (int)(360 / triangleDegrees);
		float angle = 3.1415f * 2.0f / triangles; //calculating radians
		//currently need to write 1 point per loop

		vertexArray[0] = xpos;
		vertexArray[1] = ypos;
		vertexArray[2] = 1.0f;
		vertexArray[3] = 0.5f;
		vertexArray[4] = 0.5f;

		for (int i = 1; i < triangles + 1; i++)
		{
			float nextAngle = angle * i;
			vertexArray[5 * i] = xpos + radius * sin(nextAngle);
			vertexArray[5 * i + 1] = ypos + radius * cos(nextAngle);
			vertexArray[5 * i + 2] = 1.0f;
			vertexArray[5 * i + 3] = (vertexArray[5 * i] + 1) / 2;
			vertexArray[5 * i + 4] = (vertexArray[5 * i + 1] + 1) / 2;

			indexArray[3 * (i - 1)] = 0;
			indexArray[3 * (i - 1) + 1] = i;
			indexArray[3 * (i - 1) + 2] = (i + 1 > triangles) ? 1 : i + 1;
		}
	}
	
	if (!generateTextured)
	{
		for (int i = 1; i < bufferSizes.vertexBufferSize + 1; i++)
		{
			std::cout << *(vertexArray + i - 1) << " ";
			if (i % 3 == 0)
			{
				std::cout << std::endl;
			}
		}
	}
	else
	{
		for (int i = 1; i < bufferSizes.vertexBufferSize + 1; i++)
		{
			std::cout << *(vertexArray + i - 1) << " ";
			if (i % 5 == 0)
			{
				std::cout << std::endl;
			}
		}
	}
	

	for (int i = 1; i < bufferSizes.elementBufferSize + 1; i++)
	{
		std::cout << *(indexArray + i - 1) << " ";
		if (i % 3 == 0)
		{
			std::cout << std::endl;
		}
	}

	return bufferSizes;
}
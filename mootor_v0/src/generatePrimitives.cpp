#include <iostream>
#include <math.h>

#include "generatePrimitives.h"

//always returns an array with 12 floats to targetArray 4 * {x, y, z}
//index array passed to the function should always have a 6 uint allocation
bufferSizeStore genSquare(bool generateTextured, float*& vertexArray, unsigned int*& indexArray, float width, float height, float xpos, float ypos)
{
	if (!generateTextured)
		//we can just write striaght to vertexArray here, make that change later
	{
		bufferSizeStore bufferSizes;
		bufferSizes.elementBufferSize = 6;
		bufferSizes.vertexBufferSize = 12;

		vertexArray = new float[bufferSizes.vertexBufferSize] {0};
		indexArray = new unsigned int[bufferSizes.elementBufferSize] {0};

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

		return bufferSizes;
	}
	else
	{
		bufferSizeStore bufferSizes;
		bufferSizes.elementBufferSize = 6;
		bufferSizes.vertexBufferSize = 20;

		vertexArray = new float[bufferSizes.vertexBufferSize] {0};
		indexArray = new unsigned int[bufferSizes.elementBufferSize] {0};

		for (int i = 1; i < 5; i++)
		{
			*(vertexArray + 5 * i - 3) = 1.0f;
		}

		*vertexArray = xpos + 0.0f;
		*(vertexArray + 1) = ypos + height;
		*(vertexArray + 3) = 0.0f;
		*(vertexArray + 4) = 1.0f;

		*(vertexArray + 5) = xpos + 0.0f;
		*(vertexArray + 6) = ypos + 0.0f;
		*(vertexArray + 8) = 0.0f;
		*(vertexArray + 9) = 0.0f;

		*(vertexArray + 10) = xpos + width;
		*(vertexArray + 11) = ypos + 0.0f;
		*(vertexArray + 13) = 1.0f;
		*(vertexArray + 14) = 0.0f;


		*(vertexArray + 15) = xpos + width;
		*(vertexArray + 16) = ypos + height;
		*(vertexArray + 18) = 1.0f;
		*(vertexArray + 19) = 1.0f;

		*indexArray = 0;
		*(indexArray + 1) = 1;
		*(indexArray + 2) = 2;
		*(indexArray + 3) = 2;
		*(indexArray + 4) = 3;
		*(indexArray + 5) = 0;

		for (int i = 0; i < 20; i++)
		{
			std::cout << vertexArray[i] << " ";

			if (i % 5 == 4)
			{
				std::cout << std::endl;
			}
		}

		return bufferSizes;
	}
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
		std::cout << bufferSizes.vertexBufferSize << std::endl;
		std::cout << bufferSizes.elementBufferSize << std::endl;

		vertexArray = new float[bufferSizes.vertexBufferSize] {0};
		indexArray = new unsigned int[bufferSizes.elementBufferSize] {0};

		int triangles = (int)(360 / triangleDegrees);
		std::cout << triangles << std::endl;
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
			//we are somehow generating the next position in the sequence????
			vertexArray[5 * i + 3] = 0.5f + 0.5f * sin(nextAngle);
			vertexArray[5 * i + 4] = 0.5f + 0.5f * cos(nextAngle);

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
		for (int i = 0; i < bufferSizes.vertexBufferSize + 0; i++)
		{
			std::cout << *(vertexArray + i) << " ";
			if (i % 5 == 4)
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

bufferSizeStore genTileMap(float* tilemap_buffer, unsigned int* index_buffer, int tilemap_width, int tilemap_height, int tileside_pixels)
{
	bufferSizeStore FML;

	int variablesize = tilemap_width * tilemap_height * 4 * 5;
	FML.vertexBufferSize = variablesize;
	tilemap_buffer = new float[variablesize];

	variablesize = tilemap_width * tilemap_height * 3 * 2;
	FML.elementBufferSize = variablesize;
	index_buffer = new unsigned int[variablesize];

	int nomer1 = 0, nomer2 = 0;

	for (int i = 0; i < tilemap_height; i++)
	{
		for (int i = 0; i < tilemap_width; i++)
		{
			//upper left corner of tile
			tilemap_buffer[i * 20] = nomer1;
			tilemap_buffer[i * 20 + 1] = -nomer2;
			tilemap_buffer[i * 20 + 2] = 0.0f;
			tilemap_buffer[i * 20 + 3] = 0.0f;
			tilemap_buffer[i * 20 + 4] = 1.0f;

			//upper right corner of tile
			tilemap_buffer[i * 20 + 5] = (float)tileside_pixels + nomer1;
			tilemap_buffer[i * 20 + 6] = -nomer2;
			tilemap_buffer[i * 20 + 7] = 0.0f;
			tilemap_buffer[i * 20 + 8] = 1.0f;
			tilemap_buffer[i * 20 + 9] = 1.0f;

			//lower left corner of tile
			tilemap_buffer[i * 20 + 10] = nomer1;
			tilemap_buffer[i * 20 + 11] = -(float)tileside_pixels - nomer2;
			tilemap_buffer[i * 20 + 12] = 0.0f;
			tilemap_buffer[i * 20 + 13] = 0.0f;
			tilemap_buffer[i * 20 + 14] = 0.0f;

			//lower right corner of tile
			tilemap_buffer[i * 20 + 15] = (float)tileside_pixels + nomer1;
			tilemap_buffer[i * 20 + 16] = -(float)tileside_pixels - nomer2;
			tilemap_buffer[i * 20 + 17] = 0.0f;
			tilemap_buffer[i * 20 + 18] = 1.0f;
			tilemap_buffer[i * 20 + 19] = 0.0f;

			index_buffer[i * 6] = i * 4;
			index_buffer[i * 6 + 1] = i * 4 + 1;
			index_buffer[i * 6 + 2] = i * 4 + 2;
			index_buffer[i * 6 + 3] = i * 4 + 1;
			index_buffer[i * 6 + 4] = i * 4 + 2;
			index_buffer[i * 6 + 5] = i * 4 + 3;

			nomer1 += tileside_pixels;
		}
		nomer2 += tileside_pixels;
	}


	//temporary printing
	std::cout << FML.vertexBufferSize << FML.elementBufferSize << "\n";

	for (int i = 0; i < tilemap_width; i++)
	{
		for (int i = 0; i < tilemap_height * 4; i++)
		{
			std::cout << tilemap_buffer[i * 5] << " ";
			std::cout << tilemap_buffer[i * 5 + 1] << " ";
			std::cout << tilemap_buffer[i * 5 + 2] << " ";
			std::cout << tilemap_buffer[i * 5 + 3] << " ";
			std::cout << tilemap_buffer[i * 5 + 4] << "\n";
		}
	}

	system("pause");

	return FML;
}
#include <iostream>
#include <math.h>

#include "generatePrimitives.h"

//always returns an array with 12 floats to targetArray 4 * {x, y, z}
//index array passed to the function should always have a 6 uint allocation
bufferSizeStore genSquare(bool generateTextured, float*& vertexArray, unsigned int*& indexArray, float width, float height, float xpos, float ypos)
{
	if (!generateTextured) // DEPRECTAED
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
		bufferSizes.vertexBufferSize = 24;

		vertexArray = new float[bufferSizes.vertexBufferSize] {0};
		indexArray = new unsigned int[bufferSizes.elementBufferSize] {0};

		for (int i = 1; i < 5; i++)
		{
			*(vertexArray + 6 * i - 4) = 1.0f;
		}

		*vertexArray = xpos + 0.0f;
		*(vertexArray + 1) = ypos;
		*(vertexArray + 3) = 0.0f;
		*(vertexArray + 4) = 1.0f;
		*(vertexArray + 5) = 1.0f;

		*(vertexArray + 6) = xpos + 0.0f;
		*(vertexArray + 7) = ypos - height;
		*(vertexArray + 9) = 0.0f;
		*(vertexArray + 10) = 0.0f;
		*(vertexArray + 11) = 1.0f;

		*(vertexArray + 12) = xpos + width;
		*(vertexArray + 13) = ypos - height;
		*(vertexArray + 15) = 1.0f;
		*(vertexArray + 16) = 0.0f;
		*(vertexArray + 17) = 1.0f;


		*(vertexArray + 18) = xpos + width;
		*(vertexArray + 19) = ypos;
		*(vertexArray + 21) = 1.0f;
		*(vertexArray + 22) = 1.0f;
		*(vertexArray + 23) = 1.0f;

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

	if (!generateTextured) //deprecated
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
		bufferSizes.vertexBufferSize = (bufferSizes.elementBufferSize + 3) / 3 * 6;
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
		vertexArray[5] = 1.0f;

		for (int i = 1; i < triangles + 1; i++)
		{
			float nextAngle = angle * i;
			vertexArray[6 * i] = xpos + radius * sin(nextAngle);
			vertexArray[6 * i + 1] = ypos + radius * cos(nextAngle);
			vertexArray[6 * i + 2] = 1.0f;
			//we are somehow generating the next position in the sequence????
			vertexArray[6 * i + 3] = 0.5f + 0.5f * sin(nextAngle);
			vertexArray[6 * i + 4] = 0.5f + 0.5f * cos(nextAngle);
			vertexArray[6 * i + 5] = 1.0f;

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

bufferSizeStore genTileMap(float*& tilemap_buffer, unsigned int*& index_buffer, int tilemap_width, int tilemap_height, int tileside_pixels, float position[2])
{
	bufferSizeStore FML;

	int variablesize = tilemap_width * tilemap_height * 4 * 6;
	FML.vertexBufferSize = variablesize;
	tilemap_buffer = new float[variablesize];

	variablesize = tilemap_width * tilemap_height * 3 * 2;
	FML.elementBufferSize = variablesize;
	index_buffer = new unsigned int[variablesize];

	float nomer1 = 0.0f + position[0];
	float nomer2 = 0.0f - position[1];

	for (int i = 0; i < tilemap_height; i++)
	{
		for (int j = 0; j < tilemap_width; j++)
		{
			//upper left corner of tile
			tilemap_buffer[i * tilemap_width * 24 + j * 24] = nomer1;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 1] = -nomer2;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 2] = 0.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 3] = 0.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 4] = 1.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 5] = 1.0f;

			//upper right corner of tile
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 6] = (float)tileside_pixels + nomer1;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 7] = -nomer2;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 8] = 0.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 9] = 1.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 10] = 1.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 11] = 1.0f;

			//lower left corner of tile
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 12] = nomer1;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 13] = -(float)tileside_pixels - nomer2;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 14] = 0.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 15] = 0.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 16] = 0.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 17] = 1.0f;

			//lower right corner of tile
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 18] = (float)tileside_pixels + nomer1;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 19] = -(float)tileside_pixels - nomer2;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 20] = 0.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 21] = 1.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 22] = 0.0f;
			tilemap_buffer[i * tilemap_width * 24 + j * 24 + 23] = 1.0f;

			index_buffer[i * tilemap_width * 6 + j * 6] = i * tilemap_width * 4 + j * 4;
			index_buffer[i * tilemap_width * 6 + j * 6 + 1] = i * tilemap_width * 4 + j * 4 + 1;
			index_buffer[i * tilemap_width * 6 + j * 6 + 2] = i * tilemap_width * 4 + j * 4 + 2;
			index_buffer[i * tilemap_width * 6 + j * 6 + 3] = i * tilemap_width * 4 + j * 4 + 1;
			index_buffer[i * tilemap_width * 6 + j * 6 + 4] = i * tilemap_width * 4 + j * 4 + 2;
			index_buffer[i * tilemap_width * 6 + j * 6 + 5] = i * tilemap_width * 4 + j * 4 + 3;

			nomer1 += (float)tileside_pixels;
		}
		nomer2 += (float)tileside_pixels;
		nomer1 = 0.0f + position[0];
	}

	/*
	//temporary printing
	std::cout << FML.vertexBufferSize << " " << FML.elementBufferSize << "\n";

	int magicint = 0;
	for (int i = 0; i < tilemap_height; i++)
	{
		for (int j = 0; j < tilemap_width * 4; j++)
		{
			std::cout << tilemap_buffer[i * tilemap_width * 24 + j * 6] << " ";
			std::cout << tilemap_buffer[i * tilemap_width * 24 + j * 6 + 1] << " ";
			std::cout << tilemap_buffer[i * tilemap_width * 24 + j * 6 + 2] << " ";
			std::cout << tilemap_buffer[i * tilemap_width * 24 + j * 6 + 3] << " ";
			std::cout << tilemap_buffer[i * tilemap_width * 24 + j * 6 + 4] << " ";
			std::cout << tilemap_buffer[i * tilemap_width * 24 + j * 6 + 5] << "\n";

			magicint++;
		}
	}

	std::cout << "\n";

	
	for (int i = 0; i < variablesize; i++)
	{
		std::cout << index_buffer[i] << " ";

		if (i % 3 == 2)
		{
			std::cout << "\n";
		}
	}
	
	std::cout << sizeof(index_buffer) << " " << variablesize << "\n";
	std::cout << magicint << '\n';

	system("pause");
	*/

	return FML;
}
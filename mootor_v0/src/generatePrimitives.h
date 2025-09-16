#pragma once

struct bufferSizeStore
{
	int vertexBufferSize = 0, elementBufferSize = 0;
};

void genSquare(float* vertexArray, unsigned int* indexArray, float width, float height, float xpos, float ypos);
int calcCircleVBufferSize(float degreesPerTriangle);
bufferSizeStore genCircle(bool generateTextured, float*& vertexArray, unsigned int*& indexArray, float triangleDegrees, float radius, float xpos, float ypos);
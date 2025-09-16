#pragma once

void genSquare(float* vertexArray, unsigned int* indexArray, float width, float height, float xpos, float ypos);
int calcCircleVBufferSize(float degreesPerTriangle);
void genCircle(float*& vertexArray, unsigned int*& indexArray, float triangleDegrees, float radius, float xpos, float ypos);
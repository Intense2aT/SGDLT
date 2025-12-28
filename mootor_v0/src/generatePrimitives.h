#pragma once

struct bufferSizeStore
{
	int vertexBufferSize = 0, elementBufferSize = 0;
};

bufferSizeStore genSquare(bool generateTextured, float*& vertexArray, unsigned int*& indexArray, float width, float height, float xpos, float ypos);
int calcCircleVBufferSize(float degreesPerTriangle);
bufferSizeStore genCircle(bool generateTextured, float*& vertexArray, unsigned int*& indexArray, float triangleDegrees, float radius, float xpos, float ypos);
bufferSizeStore genTileMap(float*& tilemap_buffer, unsigned int*& index_buffer, int tilemap_width, int tilemap_height, int tileside_pixels);
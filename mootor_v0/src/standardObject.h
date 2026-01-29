#pragma once
//#include "initit.h"
#include "shaderLoader.h"

class mootor;

class standardObject
{
private:
	float originPosition[2]; //global position (need a matrix for this to display relative to current coordinates)

	void addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size);

	int texmap[2] = { 0, 0 };
	int texmapitems = 0;
public:
	mootor* motor;

	unsigned int VBuffer, EBuffer, VArray;

	float* vertexBuffer;
	unsigned int* elementBuffer; //indeks buffer

	unsigned int texture;

	int amountDrawn;
	const bool textured;

	standardObject(float x_position, float y_position, mootor* mootor, bool isTextured = false);
	~standardObject();

	//float* getOriginPosition();

	// instead of doing everything manually outside, lets make it really simple and do it in the object
	// code should look like:
	// 
	// standardObject Object;
	// Object.MakeCircle(radius, Position_x, Position_y);
	// 
	// then in loop
	// Object.Draw();

	//MakeCircle uses 5 degrees per triangle by default because it looked nice at 6.0f but i want to give some leeway
	void MakeCircle(float radius, float degreesPerTriangle = 5.0f);
	void MakeSquare(float width, float height); //implement soon its not hard

	void addTexture(const char* filepath, int texmap_width, int texmap_height, int items_in_map);

	void Draw(shaderManager& base) const;

	//void BindObject(); likely decommisioned, we bind on draw
};

class buttonObject : public standardObject
{
private:
	double mouseCords[2] = { 0, 0 };
	void refreshMousePosition();
public:
	using standardObject::standardObject;
};

class playerObject : public standardObject
{

};

class tilemap
{
private:
	unsigned int VBuffer, EBuffer, VArray;
	int amountDrawn = 0;

	float* tilemap_buffer;
	int vbSize;
	unsigned int* index_buffer;
	int ibSize;

	int texmapitems = 0;
public:
	int texmap[2] = { 0, 0 };
	unsigned int texture;
	//default constructor will autamatically put top right of the tilemap to [0, 0] IF NO OTHER POSITION FOR IT IS SPECIFIED
	//tileside is the size of the side of a tile in the tilemap
	//tilemap sizes are ints to represent how many tiles are in the tilemap
	tilemap(int tileside_pixels, int tilemap_width, int tilemap_height, float position[2]);

	void addTexture(const char* filepath, int texmap_width, int texmap_height, int items_in_map);
	void addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size);
	void Draw(shaderManager& base);

	~tilemap();
};
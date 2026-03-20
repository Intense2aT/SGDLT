#pragma once
//#include "initit.h"
#include "shaderLoader.h"

class mootor;

class standardObject
{
private:

public:
	float objectPosition[2]; //global position (need a matrix for this to display relative to current coordinates)
	float objectDimensions[2];
	float objectRotation = 0.0f;
	float modelMat[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	void addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size, bool deletePreviousBuffers);

	int texmap[2] = { 0, 0 };
	int texmapitems = 0;
	int vbSize = 0, ibSize = 0;

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
	void MakeTriangle(float width, float height);
	void MakeSquare(float width, float height); //implement soon its not hard
	void MakeCustom(float* vertex_buffer, int vbSize, unsigned int* index_buffer, int ibSize);

	void addTexture(const char* filepath, int texmap_width, int texmap_height, int items_in_map);
	//swapping the cord on the texture map, texture map remains the same
	//could be done better inside shader but that means rewriting it
	void softSwapTexture(const float& tilemapNum);

	//rotation always happens on the Z axis since 3d means effort
	void SetObjectRotation(const float& deg);
	void RotateObject(const float& deg);

	void SetObjectPosition(float* pos);
	void MoveObject(float* vec);

	void Draw(shaderManager& base) const;

	//void BindObject(); likely decommisioned, we bind on draw
};


//NOT FINISHED
class buttonObject : public standardObject
{
private:
	void (*OnClick)(buttonObject*) = 0;
public:
	using standardObject::standardObject;

	void setOnClick(void (*func)(buttonObject*));

	//detecting mouse collision while clicking
	//assumption is that the button is a rectangle
	bool checkClick(bool centerMouseCords = true);
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
	unsigned int* index_buffer;
	int vbSize, ibSize;

	int texmapitems = 0;
public:
	int texmap[2] = { 0, 0 };
	unsigned int texture;
	//default constructor will autamatically put top right of the tilemap to [0, 0] IF NO OTHER POSITION FOR IT IS SPECIFIED
	//tileside is the size of the side of a tile in the tilemap
	//tilemap sizes are ints to represent how many tiles are in the tilemap
	tilemap(int tileside_pixels, int tilemap_width, int tilemap_height, float position[2]);

	void addTexture(const char* filepath, int texmap_width, int texmap_height, int items_in_map);
	void softSwapTexture(const float& tilemapNum);

	void addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size);
	void Draw(shaderManager& base);

	~tilemap();
};

struct textObjectSettings
{
	int width = 0, height = 0;
	int textMapSize = 0;
	char* textMapTranslation = nullptr;
};

//combinedObject shall be able to be used to combine many singular standardObjects with the same texture map
//into a singular object for more efficient drawing
class combinedObject : public standardObject
{
private:
	textObjectSettings* textSettings = NULL;
public:
	int objectAmount = 0;
	int* objectEnds;

	using standardObject::standardObject;
	~combinedObject();
	void addTextSettings(textObjectSettings* textSettings);
	void addObject(standardObject* object);
	void addObjectList(standardObject** objectPointer, const unsigned int& numberOfObjects);

	void makeText(const char* text, unsigned int textLenght, bool forceClearObjectData = true);

	//object number is the number of the ending in the objectEnds object endpoints list
	//in simple terms, it is the number of objects after it was added
	//example: object added third is 3
	//if nothing else is specified, default is 1
	//0 will return an unhandled error and undefined behavior, don't do / fix that
	void softSwapTextureInstance(const float& tilemapNum, const unsigned int& objectNumber = 1);
};
#pragma once

class standardObject
{
private:
	float originPosition[2];

	void addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size);
public:
	unsigned int VBuffer, EBuffer, VArray;

	float* vertexBuffer;
	unsigned int* elementBuffer; //indeks buffer

	unsigned int texture;

	int amountDrawn;
	const bool textured;

	standardObject(float x_position, float y_position, bool isTextured = false);
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

	void addTexture();

	void Draw() const;

	//void BindObject(); likely decommisioned, we bind on draw
};
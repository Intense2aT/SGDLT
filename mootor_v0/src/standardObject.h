#pragma once

class standardObject
{
private:
	void addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size);
public:
	unsigned int VBuffer, EBuffer, VArray;
	int amountDrawn;
	bool textured;

	standardObject(bool isTextured = false);
	~standardObject();
	
	// instead of doing everything manually outside, lets make it really simple and do it in the object
	// code should look like:
	// 
	// standardObject Object;
	// Object.MakeCircle(radius, Position_x, Position_y);
	// 
	// then in loop
	// Object.Draw();

	void MakeCircle();
	void MakeSquare();

	//void addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size);
	void Draw();

	//void BindObject(); likely decommisioned, we bind on draw
};
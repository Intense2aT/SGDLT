#pragma once

class standardObject
{
public:
	unsigned int VBuffer, EBuffer, VArray;
	int amountDrawn;

	standardObject();
	~standardObject();
	
	void addData(float* vertecies, int vertecies_Size, unsigned int* indicies, int indicies_Size);
	void Draw();

	//void BindObject(); likely decommisioned, we bind on draw
};
#pragma once
#include "NTypes.h"

class Buffer
{
private:
	unsigned int* color;
	int w;
	int h;
	int size;
	
public:
	Buffer(int weight, int height);

	void SetSize(int weight, int height);
	void ClearColor(unsigned int pickedColor);

	bool Save();

	void Triangle(float2 v1, float2 v2, float2 v3, unsigned int color);

	void ColorHalf(float2 v1, float2 v2, unsigned int pickedColor);
};


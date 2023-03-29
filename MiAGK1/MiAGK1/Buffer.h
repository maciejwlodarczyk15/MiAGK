#pragma once
#include "NTypes.h"

class Buffer
{
private:
	
	int w;
	int h;
	int size;
	
public:
	Buffer(int weight, int height);
	Buffer();

	unsigned int* color;

	void SetSize(int weight, int height);
	void ClearColor(unsigned int pickedColor);

	void Display();

	bool Save();

	void ClearDepthBuffer();

	int GetWidth();
	int GetHeight();

	unsigned int GetColor(int index);
	void SetColor(int index, unsigned int value);
	void SetColor(int index, float value);

	void Triangle(float3 v1, float3 v2, float3 v3, float4 color1, float4 color2, float4 color3, Buffer dbuffer, float4x4 matrix);
};


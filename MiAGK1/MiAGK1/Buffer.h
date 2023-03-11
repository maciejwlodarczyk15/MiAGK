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

	void ClearDepthBuffer();

	void Triangle(float3 v1, float3 v2, float3 v3, float4 color1, float4 color2, float4 color3, Buffer dbuffer, float4x4 pmatrix);
};


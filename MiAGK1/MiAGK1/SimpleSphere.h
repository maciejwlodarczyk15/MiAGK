#pragma once
#include "Buffer.h"
class SimpleSphere
{
private:
	int vert;
	int horiz;
	int tSize;
	float3* vertices;
	int3* indices;

public:
	SimpleSphere(int vert, int horiz);
	void Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix);
};


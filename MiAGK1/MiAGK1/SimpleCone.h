#pragma once

#include <vector>
#include "Ntypes.h"
#include "Buffer.h"

class SimpleCone
{
private:
	float3 position;
	float radius;
	float height;
	int vertexNumber;
	std::vector<float3> vertices;

public:
	SimpleCone(float3 pos, float r, float h, int vNumber);

	void Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix, float4 color);
};


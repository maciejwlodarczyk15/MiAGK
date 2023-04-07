#pragma once

#include "Ntypes.h"
#include "Buffer.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include <vector>

class SimpleSphere
{
private:
	float3 position;
	float radius;
	int vert;
	int horiz;
	std::vector<float3> vertices;

public:
	SimpleSphere(float3 pos, float r, int v, int h);
	void Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix, DirectionalLight dLight, float4x4 modelM, PointLight pLight, float3 cameraPosition);
};


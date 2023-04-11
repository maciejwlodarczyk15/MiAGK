#pragma once

#include "Buffer.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include <vector>

class SimpleTriangle
{
private:
	float3 vertices[3];
	float4 colors[3];
	float3 normal[3];
	float2 textures[3];

public:
	SimpleTriangle(float3 v1, float3 v2, float3 v3, float4 c1, float4 c2, float4 c3, float3 n1, float3 n2, float3 n3, float2 t1, float2 t2, float2 t3);
	void Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix, DirectionalLight dLight, float4x4 modelM, PointLight pLight, float3 cameraPosition, float3 cameraTarget, Buffer tBuffer, bool isLit);
};


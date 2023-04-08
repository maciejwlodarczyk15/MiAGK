#pragma once

#include <vector>
#include "Ntypes.h"
#include "Buffer.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class SimpleCone
{
private:
	float3 position;
	float radius;
	float height;
	int vertexNumber;
	std::vector<float3> vertices;
	std::vector<float3> normals;

public:
	SimpleCone(float3 pos, float r, float h, int vNumber);

	void Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix, DirectionalLight dLight, float4x4 modelM, PointLight pLight, float3 cameraPosition, float3 cameraTarget);

	void CalculateNormals();
};


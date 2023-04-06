#pragma once
#include "NTypes.h"

class DirectionalLight
{
private:
	float3 direction;
	float4 color;

public:
	DirectionalLight(float3 pos, float4 col);
	DirectionalLight();
};


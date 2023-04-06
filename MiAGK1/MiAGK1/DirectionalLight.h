#pragma once
#include "NTypes.h"

class DirectionalLight
{
private:
	float3 direction;
	float3 color;

public:
	DirectionalLight(float3 pos, float3 col);
	DirectionalLight();

	float3 GetDirection();
	float3 GetColor();
};


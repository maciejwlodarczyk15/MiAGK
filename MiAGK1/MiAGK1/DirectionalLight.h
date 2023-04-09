#pragma once
#include "NTypes.h"

class DirectionalLight
{
private:
	float3 direction;
	float3 color;
	float3 specularColor;

public:
	DirectionalLight(float3 pos, float3 col, float3 specCol);
	DirectionalLight();

	float3 GetDirection();
	float3 GetColor();
	float3 GetSpecularColor();
};


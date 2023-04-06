#pragma once

#include "NTypes.h"

class PointLight
{
private:
	float3 position;
	float3 color;
	float intensity;
	float range;
	float constant;
	float linear;
	float quadratic;

public:
	PointLight(float3 pos, float3 col, float intensity, float range, float constant, float linear, float quadratic);
	PointLight();

	float3 GetPosition();
	float3 GetColor();
	float GetIntensity();
	float GetRange();
	float GetConstant();
	float GetLinear();
	float GetQuadratic();
};


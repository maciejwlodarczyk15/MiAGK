#include "PointLight.h"

PointLight::PointLight(float3 pos, float3 col, float3 specCol, float intensity, float range, float constant, float linear, float quadratic)
{
	position = pos;
	color = col;
	specularColor = specCol;
	this->intensity = intensity;
	this->range = range;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

PointLight::PointLight()
{
	position = float3(0.0f, 0.0f, 0.0f);
	color = float3(1.0f, 1.0f, 1.0f);
	intensity = 1.0f;
	range = 1.0f;
	constant = 1.0f;
	linear = 1.0f;
	quadratic = 1.0f;
}

float3 PointLight::GetPosition()
{
	return position;
}

float3 PointLight::GetColor()
{
	return color;
}

float3 PointLight::GetSpecularColor()
{
	return specularColor;
}

float PointLight::GetIntensity()
{
	return intensity;
}

float PointLight::GetRange()
{
	return range;
}

float PointLight::GetConstant()
{
	return constant;
}

float PointLight::GetLinear()
{
	return linear;
}

float PointLight::GetQuadratic()
{
	return quadratic;
}

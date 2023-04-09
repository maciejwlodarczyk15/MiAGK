#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(float3 dir, float3 col, float3 specCol)
{
	direction = dir;
	color = col;
	specularColor = specCol;
}

DirectionalLight::DirectionalLight()
{
	direction = float3(0,0,0);
	color = float3(1,1,1);
}

float3 DirectionalLight::GetDirection()
{
	return direction;
}

float3 DirectionalLight::GetColor()
{
	return color;
}

float3 DirectionalLight::GetSpecularColor()
{
	return specularColor;
}

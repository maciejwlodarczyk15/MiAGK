#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(float3 dir, float4 col)
{
	direction = dir;
	color = col;
}

DirectionalLight::DirectionalLight()
{
	direction = float3(0,0,0);
	color = float4(1,1,1,1);
}

#pragma once
struct float3 
{
	float x, y, z;
	float3 operator+(float3 o)
	{
		float3 xd;
		xd.x = x + o.x;
		xd.y = y + o.y;
		xd.z = z + o.z;

		return xd;
	}
	// float3 operator*(float o)
	// {
	// 	float xd;
	// 	xd.x = x * o.x;
	// 	xd.y = x * o.y;
	// 	xd.z = x * o.z;
	// }
	float3 operator*(float o)
	{
		float3 xd;
		xd.x = x * o;
		xd.y = y * o;
		xd.z = z * o;
		return xd;
	}
};


struct float2 
{
	float x, y;
};

struct float4
{
	float x, y, z, w;
	float4 operator+(float4 o)
	{
		float4 xd;
		xd.x = x + o.x;
		xd.y = y + o.y;
		xd.z = z + o.z;
		xd.w = w + o.w;

		return xd;
	}
	float4 operator*(float o)
	{
		float4 xd;
		xd.x = x * o;
		xd.y = y * o;
		xd.z = z * o;
		xd.w = w * o;
		return xd;
	}
};


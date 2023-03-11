#pragma once
#include <iostream>

struct float4x4
{
	float m[4][4];

	float4x4()
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] = 0.0f;
			}
		}
	}

	float4x4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}

	void WriteToConsole()
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << m[i][j] << ", ";
			}
			std::cout << std::endl;
		}
	}
};

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
	float3 operator*(float o)
	{
		float3 xd;
		xd.x = x * o;
		xd.y = y * o;
		xd.z = z * o;
		return xd;
	}
	float3 operator*(float4x4 m)
	{
		float3 result;
		result.x = this->x * m.m[0][0] + this->y * m.m[1][0] + this->z * m.m[2][0] + 1.0f * m.m[3][0];
		result.y = this->x * m.m[0][1] + this->y * m.m[1][1] + this->z * m.m[2][1] + 1.0f * m.m[3][1];
		result.z = this->x * m.m[0][2] + this->y * m.m[1][2] + this->z * m.m[2][2] + 1.0f * m.m[3][2];
		float w  = this->x * m.m[0][3] + this->y * m.m[1][3] + this->z * m.m[2][3] + 1.0f * m.m[3][3];

		// result / w = perspective
		if (w != 0)
		{
			result.x /= w;
			result.y /= w;
			result.z /= w;
		}

		return result;
	}
	void WriteToConsole()
	{
		std::cout << "(" << x << ", " << y << ", " << z << ")\n";
	}
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


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

	float4x4 operator*(float4x4 m2)
	{
		float4x4 result;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result.m[i][j] = 0.0f;

				for (int k = 0; k < 4; ++k)
				{
					result.m[i][j] += m[i][k] * m2.m[k][j];
				}
			}
		}

		return result;
	}

	void WriteToConsole();
	float4x4 Identity();
};

struct float3 
{
	float x, y, z;
	float3() : x(0.0f), y(0.0f), z(0.0f) {}
	float3(float x, float y, float z): x(x), y(y), z(z) {}
	float3 operator+(float3 o)
	{
		float3 xd;
		xd.x = x + o.x;
		xd.y = y + o.y;
		xd.z = z + o.z;

		return xd;
	}
	float3 operator-(float3 o)
	{
		return float3(x - o.x, y - o.y, z - o.z);
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
	float3 operator/(float o)
	{
		return float3(x /o, y/o, z/o);
	}
	void WriteToConsole();
	float3 Cross(float3 v2);
	float3 Normalize();
	float Length();
	float Dot(float3 v2);
};

struct float4
{
	float x, y, z, w;
	float4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
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
	float4 operator*(float4x4 m)
	{
		float4 result;
		result.x = this->x * m.m[0][0] + this->x * m.m[1][0] + this->x * m.m[2][0] + this->x * m.m[3][0];
		result.y = this->y * m.m[0][1] + this->y * m.m[1][1] + this->y * m.m[2][1] + this->y * m.m[3][1];
		result.z = this->z * m.m[0][2] + this->z * m.m[1][2] + this->z * m.m[2][2] + this->z * m.m[3][2];
		result.w = this->w * m.m[0][3] + this->w * m.m[1][3] + this->w * m.m[2][3] + this->w * m.m[3][3];
		return result;
	}
	void WriteToConsole();
	float4x4 multByTanslation(float3 v);
	float4x4 multByScale(float3 v);
	float4x4 multByRotation(float a, float3 v);
};


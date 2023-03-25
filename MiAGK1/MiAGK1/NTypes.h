#pragma once
#include <iostream>

struct float3
{
	float x, y, z;
	float3() : x(0.0f), y(0.0f), z(0.0f) {}
	float3(float x, float y, float z) : x(x), y(y), z(z) {}
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
	float3 operator/(float o)
	{
		return float3(x / o, y / o, z / o);
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

	float4 operator/(float o)
	{
		return float4(x / o, y / o, z / o, w / o);
	}

	void WriteToConsole();
};

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

	float4x4(float4 vec1, float4 vec2, float4 vec3, float4 vec4)
	{
		m[0][0] = vec1.x; m[0][1] = vec2.x; m[0][2] = vec3.x; m[0][3] = vec4.x;
		m[1][0] = vec1.y; m[1][1] = vec2.y; m[1][2] = vec3.y; m[1][3] = vec4.y;
		m[2][0] = vec1.z; m[2][1] = vec2.z; m[2][2] = vec3.z; m[2][3] = vec4.z;
		m[3][0] = vec1.w; m[3][1] = vec2.w; m[3][2] = vec3.w; m[3][3] = vec4.w;
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

	float4 operator*(float4 vec)
	{
		float4 result;

		result.x += m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z + m[0][3] * vec.w;
		result.y += m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z + m[1][3] * vec.w;
		result.z += m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z + m[2][3] * vec.w;
		result.w += m[3][0] * vec.x + m[3][1] * vec.y + m[3][2] * vec.z + m[3][3] * vec.w;

		return result;
	}

	float4 operator*(float3 vec)
	{
		float4 result;

		result.x += m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z + m[0][3];
		result.y += m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z + m[1][3];
		result.z += m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z + m[2][3];
		result.w += m[3][0] * vec.x + m[3][1] * vec.y + m[3][2] * vec.z + m[3][3];

		return result;
	}

	float4x4 operator*(float4x4 m2)
	{
		float4x4 result;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
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
	float4x4 multByTanslation(float3 v);
	float4x4 multByScale(float3 v);
	float4x4 multByRotation(float a, float3 v);
};


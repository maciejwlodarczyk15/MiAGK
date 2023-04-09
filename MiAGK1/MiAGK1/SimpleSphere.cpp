#include "SimpleSphere.h"
#include "SimpleTriangle.h"
#include <cmath>

#define M_PI 3.14159265358979323846

SimpleSphere::SimpleSphere(float3 pos, float r, int v, int h)
{
	position = pos;
	radius = r;
	vert = v;
	horiz = h;

	// Poles 
	vertices.push_back(float3(position.x, position.y + radius, position.z));
	vertices.push_back(float3(position.x, position.y - radius, position.z));

	for (int i = 0; i < horiz; i++)
	{
		for (int j = 0; j < vert; j++)
		{
			float y = position.y + radius * std::cos((i + 1) * M_PI / (horiz + 1));
			float x = position.x + radius * std::sin((i + 1) * M_PI / (horiz + 1)) * std::sin(2 * M_PI * j / vert);
			float z = position.z + radius * std::sin((i + 1) * M_PI / (horiz + 1)) * std::cos(2 * M_PI * j / vert);
			vertices.push_back(float3(x, y, z));
		}
	}
	for (int i = 0; i < vertices.size(); i++)
	{
		normals.push_back((vertices[i]-position).Normalize());
	}

	CalculateTextures();
}

void SimpleSphere::Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix, DirectionalLight dLight, float4x4 modelM, PointLight pLight, float3 cameraPosition, float3 cameraTarget, Buffer tBuffer)
{
	// Colors
	int v1 = 0;
	int v2 = 0;
	int v3 = 0;
	int v4 = 0;
	float4 c(1.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < horiz; i++)
	{
		for (int j = 0; j < vert; j++)
		{
			// Top layer
			if (i == 0)
			{
				v1 = 0;
				v2 = (j + 1) % vert + 2;
				v3 = j + 2;
				SimpleTriangle(vertices[v1], vertices[v2], vertices[v3], c, c, c, normals[v1], normals[v2], normals[v3], textures[v1], textures[v2], textures[v3]).Draw(buff, dBuff, matrix, dLight, modelM, pLight, cameraPosition, cameraTarget, tBuffer);
			}
			// Bottom layer
			if (i == horiz - 1)
			{
				v1 = 1;
				v2 = j + 2 + (horiz - 1) * vert;
				v3 = (j + 1) % vert + 2 + (horiz - 1) * vert;
				SimpleTriangle(vertices[v1], vertices[v2], vertices[v3], c, c, c, normals[v1], normals[v2], normals[v3], textures[v1], textures[v2], textures[v3]).Draw(buff, dBuff, matrix, dLight, modelM, pLight, cameraPosition, cameraTarget, tBuffer);
			}

			// Walls
			else
			{
				v1 = 2 + j + i * vert;
				v2 = 2 + (j + 1) % vert + i * vert;
				v3 = 2 + j + (i + 1) * vert;
				v4 = 2 + (j + 1) % vert + (i + 1) * vert;
				SimpleTriangle(vertices[v1], vertices[v2], vertices[v3], c, c, c, normals[v1], normals[v2], normals[v3], textures[v1], textures[v2], textures[v3]).Draw(buff, dBuff, matrix, dLight, modelM, pLight, cameraPosition, cameraTarget, tBuffer);
				SimpleTriangle(vertices[v4], vertices[v3], vertices[v2], c, c, c, normals[v4], normals[v3], normals[v2], textures[v1], textures[v2], textures[v3]).Draw(buff, dBuff, matrix, dLight, modelM, pLight, cameraPosition, cameraTarget, tBuffer);
			}
		}
	}
}

void SimpleSphere::CalculateTextures()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		float x = vertices[i].x;
		float y = vertices[i].y;
		float z = vertices[i].z;

		float phi = atan2f(z, x);
		float theta = acosf(y / sqrt(x * x + y * y + z * z));
		
		float u = phi / (2 * M_PI) + 0.5f;
		float v = theta / M_PI;

		//float u = std::abs((x - position.x + radius) / (2 * radius));
		//float v = std::abs((y - position.y + radius) / (2 * radius));
		//
		//if (u < 0.0f) u = 0.0f;
		//if (u > 1.0f) u = 1.0f;
		//if (v < 0.0f) v = 0.0f;
		//if (v > 1.0f) v = 1.0f;

		//u = 0.5f;
		//v = 0.5f;

		textures.push_back(float2(u, v));
	}
}

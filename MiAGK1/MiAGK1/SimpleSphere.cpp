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
}

void SimpleSphere::Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix, DirectionalLight dLight, float4x4 modelM, PointLight pLight, float3 cameraPosition, float3 cameraTarget)
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
				SimpleTriangle(vertices[v1], vertices[v2], vertices[v3], c, c, c, normals[v1], normals[v2], normals[v3]).Draw(buff, dBuff, matrix, dLight, modelM, pLight, cameraPosition, cameraTarget);
			}
			// Bottom layer
			if (i == horiz - 1)
			{
				v1 = 1;
				v2 = j + 2 + (horiz - 1) * vert;
				v3 = (j + 1) % vert + 2 + (horiz - 1) * vert;
				SimpleTriangle(vertices[v1], vertices[v2], vertices[v3], c, c, c, normals[v1], normals[v2], normals[v3]).Draw(buff, dBuff, matrix, dLight, modelM, pLight, cameraPosition, cameraTarget);
			}

			// Walls
			else
			{
				v1 = 2 + j + i * vert;
				v2 = 2 + (j + 1) % vert + i * vert;
				v3 = 2 + j + (i + 1) * vert;
				v4 = 2 + (j + 1) % vert + (i + 1) * vert;
				SimpleTriangle(vertices[v1], vertices[v2], vertices[v3], c, c, c, normals[v1], normals[v2], normals[v3]).Draw(buff, dBuff, matrix, dLight, modelM, pLight, cameraPosition, cameraTarget);
				SimpleTriangle(vertices[v4], vertices[v3], vertices[v2], c, c, c, normals[v4], normals[v3], normals[v2]).Draw(buff, dBuff, matrix, dLight, modelM, pLight, cameraPosition, cameraTarget);
			}
		}
	}
}

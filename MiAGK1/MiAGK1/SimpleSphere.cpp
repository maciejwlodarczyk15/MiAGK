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
}

void SimpleSphere::Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix)
{
	// Colors
	float4 c(0.3f, 1.0f, 1.0f, 1.0f);
	float4 r(1.0f, 1.0f, 0.0f, 1.0f);
	float4 g(0.0f, 1.0f, 1.0f, 1.0f);
	float4 b(1.0f, 0.0f, 1.0f, 1.0f);
	for (int i = 0; i < horiz; i++)
	{
		for (int j = 0; j < vert; j++)
		{
			// Top layer
			if (i == 0)
			{
				SimpleTriangle(vertices[0], vertices[(j + 1) % vert + 2], vertices[j + 2], r, g, b).Draw(buff, dBuff, matrix);
			}
			// Bottom layer
			if (i == horiz - 1)
			{
				SimpleTriangle(vertices[1], vertices[j + 2 + (horiz - 1) * vert], vertices[(j + 1) % vert + 2 + (horiz - 1) * vert], r, g, b).Draw(buff, dBuff, matrix);
			}

			// Walls
			else
			{
				int v1 = 2 + j + i * vert;
				int v2 = 2 + (j + 1) % vert + i * vert;
				int v3 = 2 + j + (i + 1) * vert;
				int v4 = 2 + (j + 1) % vert + (i + 1) * vert;
				SimpleTriangle(vertices[v1], vertices[v2], vertices[v3], r, g, b).Draw(buff, dBuff, matrix);
				SimpleTriangle(vertices[v4], vertices[v3], vertices[v2], r, g, b).Draw(buff, dBuff, matrix);
			}
		}
	}
}

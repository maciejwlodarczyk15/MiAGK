#include "SimpleCone.h"
#include "SimpleTriangle.h"
#include <cmath>

#define M_PI 3.14159265358979323846

SimpleCone::SimpleCone(float3 pos, float r, float h, int vNumber)
{
	position = pos;
	radius = r;
	height = h;
	vertexNumber = vNumber;


	vertices.push_back(float3(position.x, position.y + height, position.z));
	vertices.push_back(position);
	normals.push_back(float3(0.0f, 0.0f, 0.0f));
	normals.push_back(float3(0.0f, 0.0f, 0.0f));
	for (int i = 0; i < vertexNumber; i++)
	{
		float x = std::sin(2 * M_PI * i / vertexNumber) * radius;
		float z = std::cos(2 * M_PI * i / vertexNumber) * radius;
		vertices.push_back(float3(x, position.y, z));
		normals.push_back(float3(0.0f, 0.0f, 0.0f));
	}

	CalculateNormals();
}

void SimpleCone::CalculateNormals()
{
	int v1 = 0;
	int v2 = 0;
	int v3 = 0;
	float3 v1v2;
	float3 v1v3;
	float3 normal;
	for (int i = 0; i < vertexNumber; i++)
	{
		// Wall triangles
		v1 = 0;
		v2 = (i + 1) % vertexNumber + 2;
		v3 = i + 2;

		v1v2 = vertices[v2] - vertices[v1];
		v1v3 = vertices[v3] - vertices[v1];
		normal = (-v1v2.Cross(v1v3)).Normalize();
		normals[v1] = normals[v1] + normal;
		normals[v2] = normals[v2] + normal;
		normals[v3] = normals[v3] + normal;

		// Base triangles
		v1 = 1;
		v2 = i + 2;
		v3 = (i + 1) % vertexNumber + 2;

		v1v2 = vertices[v2] - vertices[v1];
		v1v3 = vertices[v3] - vertices[v1];
		normal = (-v1v2.Cross(v1v3)).Normalize();
		normals[v1] = normals[v1] + normal;
		normals[v2] = normals[v2] + normal;
		normals[v3] = normals[v3] + normal;
	}

	for (int i = 0; i < normals.size(); i++)
	{
		normals[i].Normalize();
	}
}

void SimpleCone::Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix, DirectionalLight dLight, float4x4 modelM, PointLight pLight, float3 cameraPosition, float3 cameraTarget)
{
	// Colors
	float4 c(0.0f, 1.0f, 0.0f, 1.0f);
	int v1 = 0;
	int v2 = 0;
	int v3 = 0;
	int counter = 0;
	for (int i = 0; i < vertexNumber; i++)
	{
		// Wall triangles
		v1 = 0;
		v2 = (i + 1) % vertexNumber + 2;
		v3 = i + 2;
		SimpleTriangle triangle1(vertices[v1], vertices[v2], vertices[v3], c, c, c, normals[v1], normals[v2], normals[v3]);

		// Base triangles
		v1 = 1;
		v2 = i + 2;
		v3 = (i + 1) % vertexNumber + 2;
		SimpleTriangle triangle2(vertices[v1], vertices[v2], vertices[v3], c, c, c, normals[v1], normals[v2], normals[v3]);
		
		counter += 2;

		triangle1.Draw(buff, dBuff, matrix, dLight, modelM, pLight, cameraPosition, cameraTarget);
		triangle2.Draw(buff, dBuff, matrix, dLight, modelM, pLight, cameraPosition, cameraTarget);
	}
}

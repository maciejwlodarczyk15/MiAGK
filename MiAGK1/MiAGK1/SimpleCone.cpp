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
	for (int i = 0; i < vertexNumber; i++)
	{
		float x = std::sin(2 * M_PI * i / vertexNumber) * radius;
		float z = std::cos(2 * M_PI * i / vertexNumber) * radius;
		vertices.push_back(float3(x, position.y, z));
	}
}

void SimpleCone::Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix, float4 color)
{
	// 4 fun
	float4 red(1.0f, 0.0f, 0.0f, 1.0f);
	std::vector<float4> colors;
	colors.push_back(float4(0.0f, 1.0f, 0.0f, 1.0f));
	colors.push_back(float4(0.0f, 0.0f, 1.0f, 1.0f));
	for (int i = 0; i < vertexNumber; i++)
	{
		// Boczne trójkąty
		SimpleTriangle triangle1(vertices[0], vertices[(i + 1) % vertexNumber + 2], vertices[i + 2], red, colors[i % 2], colors[(i + 1) % 2]);
		//SimpleTriangle triangle1(vertices[0], vertices[(i + 1) % vertexNumber + 2], vertices[i + 2], red, colors[0], colors[1]);
		//vertices[0], vertices[i + 2], vertices[(i + 1) % vertexNumber + 2]

		// Trójkąty podstawy
		SimpleTriangle triangle2(vertices[1], vertices[i + 2], vertices[(i + 1) % vertexNumber + 2], red, colors[(i + 1) % 2], colors[i % 2]);
		//SimpleTriangle triangle2(vertices[1], vertices[i + 2], vertices[(i + 1) % vertexNumber + 2], red, colors[0], colors[1]);
		
		triangle1.Draw(buff, dBuff, matrix);
		triangle2.Draw(buff, dBuff, matrix);
		//vertices[1], vertices[(i + 1) % vertexNumber + 2], vertices[i + 2]
	}
}

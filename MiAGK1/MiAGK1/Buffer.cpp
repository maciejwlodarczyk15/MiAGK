#define _CRT_SECURE_NO_WARNINGS 1
#include "Buffer.h"
#include <cstdio>
#include <corecrt_math.h>
#include <utility>
#include <iostream>

Buffer::Buffer(int weight, int height)
{
	SetSize(weight, height);
}

bool Buffer::Save()
{
	unsigned short header[9] = {
		0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0100, 0x0100,
		0x0820};
	
	FILE* f = fopen("nazwapliku.tga", "wb+");
	if (NULL == f) return false;

	header[6] = w;
	header[7] = h;

	fwrite(header, 2, 9, f);
	fwrite(color, 4, size, f);
	return true;
}

void Buffer::SetSize(int width, int height)
{
	w = width;
	h = height;
	size = w * h;
	color = new unsigned int[size];
}

void Buffer::ClearColor(unsigned int pickedColor)
{
	for (unsigned int i = 0; i < size; i++) 
	{	
		color[i] = pickedColor;
	}
}

// Color half of the screen
void Buffer::ColorHalf(float2 v1, float2 v2, unsigned int pickedColor)
{
	for (int y = 0; y < h; y++) 
	{
		for (int x = 0; x < w; x++) 
		{
			float f = (v2.x - v1.x) * (y - v1.y) - (v2.y - v1.y) * (x - v1.x);

			if (f < 0)
			{
				color[y * w + x] = pickedColor;
			}
		}
	}
}

void Buffer::Triangle(float2 v1, float2 v2, float2 v3, unsigned int pickedColor)
{
	float x1 = (v1.x + 1.0f) * w * 0.5f;
	float x2 = (v2.x + 1.0f) * w * 0.5f;
	float x3 = (v3.x + 1.0f) * w * 0.5f;
	float y1 = (v1.y + 1.0f) * h * 0.5f;
	float y2 = (v2.y + 1.0f) * h * 0.5f;
	float y3 = (v3.y + 1.0f) * h * 0.5f;

	// Search rectangle
	int minX = std::min((int)x1, std::min((int)x2, (int)x3));
	int maxX = std::max((int)x1, std::max((int)x2, (int)x3));
	int minY = std::min((int)y1, std::min((int)y2, (int)y3));
	int maxY = std::max((int)y1, std::max((int)y2, (int)y3));
	
	// Edge-cutting
	minX = std::max(minX, 0);
	maxX = std::min(maxX, w - 1);
	minY = std::max(minY, 0);
	maxY = std::min(maxY, h - 1);

	// Barycentric coordinate system
	float dx13 = x1 - x3;
	float dx23 = x2 - x3;
	float dx32 = x3 - x2;
	float dy23 = y2 - y3;
	float dy13 = y1 - y3;
	float dy31 = y3 - y1;
	

	float VerticesColor;

	for (int x = minX; x < maxX; x++) {
		for (int y = minY; y < maxY; y++)
		{
			float f1 = (x1 - x2) * (y - y1) - (y1 - y2) * (x - x1);
			float f2 = (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2);
			float f3 = (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3);

			float lam1 = ( dy23 * (x - x3) + dx32 * (y - y3) / dy23*dx13 + dx32 * dy13);
			float lam2 = ( dy31 * (x - x3) + dx13 * (y - y3) / dy31 * dx23 + dx13 * dy23 );
			float lam3 = 1 - lam1 - lam2;

			if (f1 > 0 && f2 > 0 && f3 > 0) 
			{
				color[y * w + x] = pickedColor;
				//color[y * w + x] = pickedColor;
			}
		}
	}
}

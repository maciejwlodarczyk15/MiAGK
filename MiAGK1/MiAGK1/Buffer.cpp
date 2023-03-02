#define _CRT_SECURE_NO_WARNINGS 1
#include "Buffer.h"
#include <cstdio>

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

void Buffer::Triangle(float2 posX, float2 posY, float2 posZ)
{
	float x, y;
	for (int collumn = 0; collumn < h; collumn++) 
	{
		for (int row = 0; row < w; row++)
		{
			x = (row + 1) * w * 0.5f;
			y = (collumn + 1) * h * 0.5f;
			if ( (posX.x - posY.x) * (y - posX.y) - (posX.y - posY.y) * (x - posX.x) > 0
			&&   (posY.x - posZ.x) * (y - posY.y) - (posY.y - posZ.y) * (x - posY.x) > 0
			&&   (posZ.x - posX.x) * (y - posZ.y) - (posZ.y - posX.y) * (x - posZ.x) > 0
				)
			{
				color[collumn * w + row] = 0xFFFF0000;
			}
		}
	}

	// Checkboard coloring check
	//for (int i = 0; i < size; i+=2) {
	//	color[i] = 0xFFFF0000;
	//}
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

// if ((posX.x - posY.x) * (/*y*/ -posX.y) - (posX.y - posY.y) * (/*x*/ -posX.x) > 0) {}
// if ((posY.x - posZ.x) * (/*y*/ -posY.y) - (posY.y - posZ.y) * (/*x*/ -posY.x) > 0) {}
// if ((posZ.x - posX.x) * (/*y*/ -posZ.y) - (posZ.y - posX.y) * (/*x*/ -posZ.x) > 0) {}
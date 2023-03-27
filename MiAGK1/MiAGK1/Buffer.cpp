#define _CRT_SECURE_NO_WARNINGS 1
#include "Buffer.h"
#include <cstdio>
#include <corecrt_math.h>
#include <utility>
#include <iostream>
#include <opencv2/opencv.hpp>

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

void Buffer::ClearDepthBuffer()
{
	for (unsigned int i = 0; i < size; i++)
	{
		color[i] = 1000;
	}
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

void Buffer::Display()
{
	cv::Mat img(h, w, CV_8UC3, cv::Scalar(0, 0, 0));

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			unsigned int c = color[y * w + x];
			cv::Vec3b& pixel = img.at<cv::Vec3b>(y, x);

			unsigned char r = (c & 0x00ff0000) >> 16;
			unsigned char g = (c & 0x0000ff00) >> 8;
			unsigned char b = c & 0x000000ff;

			pixel[0] = b;
			pixel[1] = g;
			pixel[2] = r;
		}
	}

	cv::flip(img, img, 0); // Image had to be flipped horizontally to match the TGA file
	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", img);
	cv::waitKey(0);
}

void Buffer::Triangle(float3 v1, float3 v2, float3 v3, float4 c1, float4 c2, float4 c3, Buffer dbuffer, float4x4 matrix)
{
	float4 v1f4({ v1.x, v1.y, v1.z, 1.0f });
	float4 v2f4({ v2.x, v2.y, v2.z, 1.0f });
	float4 v3f4({ v3.x, v3.y, v3.z, 1.0f });

	float4 v1Proj(matrix * v1f4);
	float4 v2Proj(matrix * v2f4);
	float4 v3Proj(matrix * v3f4);

	float3 v1new = float3({ v1Proj.x, v1Proj.y, v1Proj.z });
	float3 v2new = float3({ v2Proj.x, v2Proj.y, v2Proj.z });
	float3 v3new = float3({ v3Proj.x, v3Proj.y, v3Proj.z });

	if (v1Proj.w != 0.0f) v1new = v1new / v1Proj.w;
	if (v2Proj.w != 0.0f) v2new = v2new / v2Proj.w;
	if (v3Proj.w != 0.0f) v3new = v3new / v3Proj.w;

	float x1 = (v1new.x + 1.0f) * w * 0.5f;
	float x2 = (v2new.x + 1.0f) * w * 0.5f;
	float x3 = (v3new.x + 1.0f) * w * 0.5f;
	float y1 = (v1new.y + 1.0f) * h * 0.5f;
	float y2 = (v2new.y + 1.0f) * h * 0.5f;
	float y3 = (v3new.y + 1.0f) * h * 0.5f;
	float z1 = v1.z;
	float z2 = v2.z;
	float z3 = v3.z;


	// Rectangle search
	int minX = std::min((int)x1, std::min((int)x2, (int)x3));
	int maxX = std::max((int)x1, std::max((int)x2, (int)x3));
	int minY = std::min((int)y1, std::min((int)y2, (int)y3));
	int maxY = std::max((int)y1, std::max((int)y2, (int)y3));

	// Edge cutting
	minX = std::max(minX, 0);
	maxX = std::min(maxX, w - 1);
	minY = std::max(minY, 0);
	maxY = std::min(maxY, h - 1);

	float dx13 = x1 - x3;
	float dx23 = x2 - x3;
	float dx32 = x3 - x2;
	float dy23 = y2 - y3;
	float dy13 = y1 - y3;
	float dy31 = y3 - y1;

	float dy12 = y1 - y2;
	float dx12 = x1 - x2;
	float dx31 = x3 - x1;

	bool tl1 = false;
	bool tl2 = false;
	bool tl3 = false;

	if (dy12 < 0 || (dy12 == 0 && dx12 > 0)) tl1 = true;
	if (dy23 < 0 || (dy23 == 0 && dx23 > 0)) tl2 = true;
	if (dy31 < 0 || (dy31 == 0 && dx31 > 0)) tl3 = true;

	for (int x = 0; x < w; x++) 
	{
		for (int y = 0; y < h; y++)
		{
			float f1 = (x1 - x2) * (y - y1) - (y1 - y2) * (x - x1);
			float f2 = (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2);
			float f3 = (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3);

			float lam1 = (dy23 * (x - x3) + dx32 * (y - y3)) / (dy23 * dx13 + dx32 * dy13);
			float lam2 = (dy31 * (x - x3) + dx13 * (y - y3)) / (dy31 * dx23 + dx13 * dy23);
			float lam3 = 1 - lam1 - lam2;

			float depth = (lam1 * v1.z + lam2 * v2.z + lam3 * v3.z);

			bool topleft1;
			bool topleft2;
			bool topleft3;

			// Top-left edge
			if (tl1) topleft1 = f1 >= 0;
			else topleft1 = f1 > 0;

			if (tl2) topleft2 = f2 >= 0;
			else topleft2 = f2 > 0;

			if (tl3) topleft3 = f3 >= 0;
			else topleft3 = f3 > 0;

			if (topleft1 && topleft2 && topleft3)
			{
				float4 cumulative = c1 * lam1 + c2 * lam2 + c3 * lam3;
				float r = cumulative.x * 255;
				float g = cumulative.y * 255;
				float b = cumulative.z * 255;
				float a = cumulative.w * 255;
				unsigned int colorValue = ((unsigned int)a << 24) | ((unsigned int)r << 16) | ((unsigned int)g << 8) | (unsigned int)b;
			
				 // Z-buffer
				 if (depth < dbuffer.color[y * w + x])
				 {
				 	color[y * w + x] = colorValue;
				 	dbuffer.color[y * w + x] = depth;
				 }
			}
		}
	}
}

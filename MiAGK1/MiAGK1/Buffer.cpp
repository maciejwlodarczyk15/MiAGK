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

Buffer::Buffer()
{
	SetSize(800, 600);
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

int Buffer::GetWidth()
{
	return w;
}

int Buffer::GetHeight()
{
	return h;
}

unsigned int Buffer::GetColor(int index)
{
	return color[index];
}

void Buffer::SetColor(int index, unsigned int value)
{
	color[index] = value;
}

void Buffer::SetColor(int index, float value)
{
	color[index] = value;
}
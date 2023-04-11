#pragma once
#include "NTypes.h"

class Buffer
{
private:
	
	int w;
	int h;
	int size;
	
public:
	Buffer(int weight, int height);
	Buffer();

	unsigned int* color;

	void SetSize(int weight, int height);
	void ClearColor(unsigned int pickedColor);

	void Display();

	bool Save(const char* filename);

	void ClearDepthBuffer();

	int GetWidth();
	int GetHeight();

	unsigned int GetColor(int index);
	void SetColor(int index, unsigned int value);

	bool Load(const char* fileName);
};


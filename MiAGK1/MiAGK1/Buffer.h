#pragma once
class Buffer
{
private:
	unsigned int* color;
	int w;
	int h;
	int size;
	
public:
	Buffer(int weight, int height);

	void SetSize(int weight, int height);
	void ClearColor(unsigned int pickedColor);

	bool Save();
};


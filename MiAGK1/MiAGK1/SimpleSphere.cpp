#include "SimpleSphere.h"
#include "NTypes.h"
#include "SimpleTriangle.h"

#define M_PI       3.14159265358979323846

SimpleSphere::SimpleSphere(int vert, int horiz)
{
	this->vert = vert;
	this->horiz = horiz;

	int vSize = vert * (horiz + 2);
	tSize = 2 * vert * horiz;
	vertices = new float3[vSize];
	indices = new int3[tSize];

	for (int yy = 0; yy <= horiz + 1; ++yy)
	{
		float y = cos(yy * M_PI / (horiz + 1.f));
		float r = sqrt(1 - y * y);
		for (int rr = 0; rr < vert; ++rr)
		{
			float x = r * cos(2 * M_PI * rr / vert);
			float z = r * sin(2 * M_PI * rr / vert);
			vertices[rr + yy * vert] = float3(x, y, z);
		}
	}

	for (int yy = 0; yy < horiz; ++yy)
	{
		for (int rr = 0; rr < vert; ++rr)
		{
			indices[rr + 2 * yy * vert] = int3(
				(rr + 1) & vert			+ yy * vert,
				rr + vert				+ yy * vert,
				(rr + 1) % vert + vert	+ yy * vert
			);
			std::cout << "Indices [rr + 2 * yy * vert] = \n"
				<< "Indices [" << rr << " + 2 * " << yy << " * " << vert << "] = \n";
			indices[rr + 2 * yy * vert].WriteToConsole();
			std::cout << std::endl << std::endl;

			indices[rr + vert + 2 * yy * vert] = int3(
				rr + vert				+ yy * vert,
				rr + 2 * vert			+ yy * vert,
				(rr + 1) % vert + vert	+ yy * vert
			);
			std::cout << "Indices [rr + vert + 2 * yy * vert] = \n"
				<< "Indices [" << rr << " + " << vert << " + 2 * " << yy << " * " << vert << "] = \n";
			indices[rr + vert + 2 * yy * vert].WriteToConsole();
			std::cout << std::endl << std::endl;
		}
	}
}

void SimpleSphere::Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix)
{
	float4 color1(1.0f, 0.0f, 0.0f, 1.0f);
	float4 color2(0.0f, 1.0f, 0.0f, 1.0f);
	float4 color3(0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0; i < tSize; ++i)
	{
		//float3 positionx = vertices[indices->x];
		//float3 positionx = vertices[indices->y];
		//float3 positionx = vertices[indices->z];
		//positionx.WriteToConsole();
		std::cout << "\n";
		indices->WriteToConsole();
		//SimpleTriangle triangle(position.x, );
		//triangle.Draw(buff, dBuff, matrix);
	}
}

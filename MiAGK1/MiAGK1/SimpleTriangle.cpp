#include "SimpleTriangle.h"

SimpleTriangle::SimpleTriangle(float3 v1, float3 v2, float3 v3, float4 c1, float4 c2, float4 c3)
{
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
	colors[0] = c1;
	colors[1] = c2;
	colors[2] = c3;
}

void SimpleTriangle::Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix, DirectionalLight dLight, float4x4 modelM, PointLight pLight, float3 cameraPosition)
{
	int w = buff.GetWidth();
	int h = buff.GetHeight();

	float4 v1f4({ vertices[0].x, vertices[0].y, vertices[0].z, 1.0f});
	float4 v2f4({ vertices[1].x, vertices[1].y, vertices[1].z, 1.0f});
	float4 v3f4({ vertices[2].x, vertices[2].y, vertices[2].z, 1.0f});

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
	float z1 = vertices[0].z;
	float z2 = vertices[1].z;
	float z3 = vertices[2].z;

	float3 oldv1(x1, y1, z1);
	float3 oldv2(x2, y2, z2);
	float3 oldv3(x3, y3, z3);

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

	// Directional light
	float3 directionalLightDirection = dLight.GetDirection();
	float3 directionalLightColor = dLight.GetColor();

	// Normals
	float3 v1v2 = vertices[1] - vertices[0];
	float3 v1v3 = vertices[2] - vertices[0];
	float3 normal = (v1v2.Cross(v1v3)).Normalize();

	// Calculate normals based on translation/rotation/scale
	normal = modelM * normal;
	
	float3 ambientColor(0.1f, 0.1f, 0.1f);
	float3 toLight = (directionalLightDirection * (-1)).Normalize();
	float intensityDirectional = std::max(0.0f, toLight.Dot(normal));

	float3 tcolor1(colors[0].x, colors[0].y, colors[0].z);
	float3 tcolor2(colors[1].x, colors[1].y, colors[1].z);
	float3 tcolor3(colors[2].x, colors[2].y, colors[2].z);

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

			float depth = (lam1 * vertices[0].z + lam2 * vertices[1].z + lam3 * vertices[2].z);

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
				// Color from vertices and lambdas
				float3 color = tcolor1 * lam1 + tcolor2 * lam2 + tcolor3 * lam3;

				// Ambient color
				float3 ambient = ambientColor * color;

				// Color of directional
				float3 diffuseDirectional = directionalLightColor * color * intensityDirectional;
				
				// POINT DIFFUSE
				float3 lightDirection = (pLight.GetPosition() - (vertices[0] * lam1 + vertices[1] * lam2 + vertices[2] * lam3)).Normalize();
				float pDiffuse = std::max(0.0f, (normal.Dot(lightDirection)));
				float3 pDiffColor = pLight.GetColor() * pDiffuse * color;

				// POINT SPECULAR
				float specularStrength = 0.5f;
				float3 viewDir = (cameraPosition - (vertices[0] * lam1 + vertices[1] * lam2 + vertices[2] * lam3)).Normalize();

				float3 reflectDir = (lightDirection * (-1)).Reflect(normal).Normalize();
				float spec = std::pow(std::max(viewDir.Dot(reflectDir), 0.0f), 32);
				float3 pSpecColor = pLight.GetColor() * color * spec * specularStrength;


				// POINT LIGHT

				//float3 toPointLight = pLight.GetPosition() - (vertices[0] * lam1 + vertices[1] * lam2 + vertices[2] * lam3);
				//float toPointLightDistance = toPointLight.Length();
				//float3 toPointLightDirection = toPointLight / toPointLightDistance;
				//
				//float intensityPoint = std::max(0.0f, toPointLightDirection.Dot(normal));
				//
				//float attenuation = 1.0f / (pLight.GetConstant() + pLight.GetLinear() * toPointLightDistance + pLight.GetQuadratic() * toPointLightDistance * toPointLightDistance);
				//float3 halfWay = (toPointLightDirection + center).Normalize();
				//float specularPoint = std::pow(std::max(0.0f, normal.Dot(halfWay)), shininess);

				//float3 lightDir = ((vertices[0] * lam1 + vertices[1] * lam2 + vertices[2] * lam3) - pLight.GetPosition()).Normalize();
				//float diff = std::max(0.0f, -normal.Dot(lightDir));
				//float3 diffusePoint = pLight.GetColor() * color * diff;
				//
				//float3 viewDir = ((vertices[0] * lam1 + vertices[1] * lam2 + vertices[2] * lam3) - eye).Normalize();
				//float3 halfwayDir = (lightDir + viewDir).Normalize();
				//
				//float specularIntensity = 4.0f;
				//float spec = pow(std::max(0.0f, normal.Dot(halfwayDir)), specularIntensity);
				//spec = pow(std::max(viewDir.Dot(lightDir - normal * normal.Dot(lightDir) * 2), 0.0f), specularIntensity);
				//float3 diffuseSpecular = pLight.GetColor() * spec;



				//float3 finalColor = ambient;
				//float3 finalColor = ambient + (/*diffuseDirectional +*/ diffusePoint);
				
				// DIFFUSE DZIALAJACY SAM
				//float3 finalColor = ambient + diffuseDirectional;

				 // LIGHT DIR = (PIXEL - LIGHT.POSITION).NORMALIZE()
				//float3 lightDir = (pLight.GetPosition() - float3(x, y, depth)).Normalize();
				//float diff = std::max(0.0f, normal.Dot(lightDir));
				//float3 diffusePoint = color * pLight.GetColor() * pLight.GetIntensity() * diff;

				//float3 finalColor = ambient + diffusePoint + diffuseSpecular;

				float3 finalColor = ambient + pDiffColor + pSpecColor;

				float r = finalColor.x * 255;
				float g = finalColor.y * 255;
				float b = finalColor.z * 255;
				float a = colors[0].w * 255;

				// Clamp color values to the range of 0-255
				r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
				g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
				b = (b < 0) ? 0 : ((b > 255) ? 255 : b);
				a = (a < 0) ? 0 : ((a > 255) ? 255 : a);

				unsigned int colorValue = ((unsigned int)a << 24) | ((unsigned int)r << 16) | ((unsigned int)g << 8) | (unsigned int)b;

				// Z-buffer
				if (depth < dBuff.GetColor(y * w + x))
				{
					buff.SetColor((y * w + x), colorValue);
					dBuff.SetColor((y * w + x), depth);
				}
			}
		}
	}
}

#include "SimpleTriangle.h"

SimpleTriangle::SimpleTriangle(float3 v1, float3 v2, float3 v3, float4 c1, float4 c2, float4 c3, float3 n1, float3 n2, float3 n3)
{
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
	colors[0] = c1;
	colors[1] = c2;
	colors[2] = c3;
	normal[0] = n1;
	normal[1] = n2;
	normal[2] = n3;
}

void SimpleTriangle::Draw(Buffer& buff, Buffer& dBuff, float4x4 matrix, DirectionalLight dLight, float4x4 modelM, PointLight pLight, float3 cameraPosition, float3 cameraTarget)
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

	// FRAGMENTOWE = ZAPIS W PETLI

	// Change colors to vec3
	float3 tcolor1(colors[0].x, colors[0].y, colors[0].z);
	float3 tcolor2(colors[1].x, colors[1].y, colors[1].z);
	float3 tcolor3(colors[2].x, colors[2].y, colors[2].z);

	// Modify normals using model matrix (to work on rotated objects)
	float3 v1Normal = modelM * this->normal[0];
	float3 v2Normal = modelM * this->normal[1];
	float3 v3Normal = modelM * this->normal[2];

	// Base color of ambient light
	float3 ambientColor(0.1f, 0.1f, 0.1f);
	// Final ambient
	float3 ambient(0.0f, 0.0f, 0.0f);

	float3 toLight = (-dLight.GetDirection()).Normalize();
	float3 viewDir = (cameraTarget - cameraPosition).Normalize();

	float specularStrength = 0.5f;
	bool isVertices = false;
	
	// Calculate light for each of the vertices
	if (isVertices)
	{
		// Direct diffuse
		float3 dDiffuse1 = dLight.GetColor() * tcolor1 * std::max(0.0f, toLight.Dot(v1Normal));
		float3 dDiffuse2 = dLight.GetColor() * tcolor2 * std::max(0.0f, toLight.Dot(v2Normal));
		float3 dDiffuse3 = dLight.GetColor() * tcolor3 * std::max(0.0f, toLight.Dot(v3Normal));

		// Direct specular
		float3 dReflect1 = dLight.GetDirection().Reflect(v1Normal).Normalize();
		float3 dReflect2 = dLight.GetDirection().Reflect(v2Normal).Normalize();
		float3 dReflect3 = dLight.GetDirection().Reflect(v3Normal).Normalize();
		float dSpec1 = std::pow(std::max(-viewDir.Dot(dReflect1), 0.0f), 24);
		float dSpec2 = std::pow(std::max(-viewDir.Dot(dReflect2), 0.0f), 24);
		float dSpec3 = std::pow(std::max(-viewDir.Dot(dReflect3), 0.0f), 24);
		float3 dSpecColor1 = dLight.GetSpecularColor() * dSpec1 * specularStrength;
		float3 dSpecColor2 = dLight.GetSpecularColor() * dSpec2 * specularStrength;
		float3 dSpecColor3 = dLight.GetSpecularColor() * dSpec3 * specularStrength;


		// Point diffuse
		float3 lightDirection1 = (vertices[0] - pLight.GetPosition()).Normalize();
		float3 lightDirection2 = (vertices[1] - pLight.GetPosition()).Normalize();
		float3 lightDirection3 = (vertices[2] - pLight.GetPosition()).Normalize();
		float pDiffuse1 = std::max(0.0f, (-v1Normal.Dot(lightDirection1)));
		float pDiffuse2 = std::max(0.0f, (-v2Normal.Dot(lightDirection2)));
		float pDiffuse3 = std::max(0.0f, (-v3Normal.Dot(lightDirection3)));
		float3 pDiffColor1 = pLight.GetColor() * tcolor1 * pDiffuse1;
		float3 pDiffColor2 = pLight.GetColor() * tcolor2 * pDiffuse2;
		float3 pDiffColor3 = pLight.GetColor() * tcolor3 * pDiffuse3;

		// Point specular
		float3 pReflectDir1 = lightDirection1.Reflect(v1Normal).Normalize();
		float3 pReflectDir2 = lightDirection2.Reflect(v2Normal).Normalize();
		float3 pReflectDir3 = lightDirection3.Reflect(v3Normal).Normalize();

		float pSpec1 = std::pow(std::max(-viewDir.Dot(pReflectDir1), 0.0f), 24);
		float pSpec2 = std::pow(std::max(-viewDir.Dot(pReflectDir2), 0.0f), 24);
		float pSpec3 = std::pow(std::max(-viewDir.Dot(pReflectDir3), 0.0f), 24);

		float3 pSpecColor1 = pLight.GetSpecularColor() * pSpec1 * specularStrength;
		float3 pSpecColor2 = pLight.GetSpecularColor() * pSpec2 * specularStrength;
		float3 pSpecColor3 = pLight.GetSpecularColor() * pSpec3 * specularStrength;



		// Sum up the whole color
		//tcolor1 = dDiffuse1 + dSpecColor1;
		//tcolor2 = dDiffuse2 + dSpecColor2;
		//tcolor3 = dDiffuse3 + dSpecColor3;

		//tcolor1 = pDiffColor1 + pSpecColor1;
		//tcolor2 = pDiffColor2 + pSpecColor2;
		//tcolor3 = pDiffColor3 + pSpecColor3;

		tcolor1 = dDiffuse1 + dSpecColor1 + pDiffColor1 + pSpecColor1;
		tcolor2 = dDiffuse2 + dSpecColor2 + pDiffColor2 + pSpecColor2;
		tcolor3 = dDiffuse3 + dSpecColor3 + pDiffColor3 + pSpecColor3;
	}

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

				// Final ambient color calculation
				float3 ambient = ambientColor * color;
				
				// Final color always have ambient
				float3 finalColor = ambient;

				// If only count on vertices -> everything saved to color
				if (isVertices)
				{
					finalColor = finalColor + color;
				}
				else
				{
					// Calculate normal in current triangle fragment
					float3 normal = (v1Normal * lam1 + v2Normal * lam2 + v3Normal * lam3).Normalize();

					// Direct diffuse
					float3 dDiffuse = dLight.GetColor() * color * std::max(0.0f, toLight.Dot(normal));

					// Direct specular
					float3 dReflect = dLight.GetDirection().Reflect(normal).Normalize();
					float dSpec = std::pow(std::max(-viewDir.Dot(dReflect), 0.0f), 24);
					float3 dSpecColor = dLight.GetSpecularColor() * dSpec * specularStrength;

					// Point diffuse
					float3 lightDirection = ((vertices[0] * lam1 + vertices[1] * lam2 + vertices[2] * lam3) - pLight.GetPosition()).Normalize();
					float pDiffuse = std::max(0.0f, (-normal.Dot(lightDirection)));
					float3 pDiffColor = pLight.GetColor() * pDiffuse * color;

					// Point specular
					float specularStrength = 0.5f;
					float3 viewDir = (cameraTarget - cameraPosition).Normalize();

					float3 reflectDir = lightDirection.Reflect(normal).Normalize();
					float spec = std::pow(std::max(-viewDir.Dot(reflectDir), 0.0f), 24);
					float3 pSpecColor = pLight.GetSpecularColor() * color * spec * specularStrength;

					//finalColor = finalColor + dDiffuse + dSpecColor;
					
					//finalColor = finalColor + pDiffColor + pSpecColor;

					finalColor = finalColor + dDiffuse + dSpecColor + pDiffColor + pSpecColor;
				}

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

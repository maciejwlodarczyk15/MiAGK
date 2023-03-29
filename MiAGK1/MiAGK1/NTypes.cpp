#include "NTypes.h"

#define M_PI 3.14159265358979323846

void float3::WriteToConsole()
{
    std::cout << "(" << x << ", " << y << ", " << z << ")\n";
}

float3 float3::Cross(float3 v2)
{
    return float3((y * v2.z - z * v2.y),
                  (z * v2.x - x * v2.z),
                  (x * v2.y - y * v2.x));
}

float3 float3::Normalize()
{
    float length = this->Length();
    if (length != 0)
    {
        float3 newVector({x /= length, y /= length, z /= length});
    }
    return float3();
}

float float3::Length()
{
    return sqrt(x * x + y * y + z * z);
}

float float3::Dot(float3 v2)
{
    return x * v2.x + y * v2.y + z * v2.z;
}

void float4x4::WriteToConsole()
{
    std::cout << "[";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << m[i][j] << ", ";
        }
        std::cout << "]\n[";
    }
    std::cout << "finished]\n\n";
}

float4x4 float4x4::Identity()
{
    return float4x4(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

float4x4 float4x4::multByTanslation(float3 v)
{
    float4x4 result;
    result = result.Identity();
    result.m[0][3] = v.x;
    result.m[1][3] = v.y;
    result.m[2][3] = v.z;
    return result;
}

float4x4 float4x4::multByScale(float3 v)
{
    float4x4 result;
    result = result.Identity();
    result.m[0][0] = v.x;
    result.m[1][1] = v.y;
    result.m[2][2] = v.z;
    return result;
}

// v - os obrotu
float4x4 float4x4::multByRotation(float a, float3 v)
{
    float s = sin(a * M_PI / 180.0f);
    float c = cos(a * M_PI / 180.0f);

    v.Normalize();

    float4x4 result(
                    v.x * v.x * (1 - c) + c,            v.y * v.x * (1 - c) - v.z * s,      v.x * v.z * (1 - c) + v.y * s,          0,
                    v.x * v.y * (1 - c) + v.z * s,      v.y * v.y * (1 - c) + c,            v.y * v.z * (1 - c) - v.x * s,          0,
                    v.x * v.z * (1 - c) - v.y * s,      v.y * v.z * (1 - c) + v.x * s,      v.z * v.z * (1 - c) + c,                0,
                    0,                                  0,                                  0,                                      1
    );

    return result;
}

void float4::WriteToConsole()
{
    std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")\n";
}

void int3::WriteToConsole()
{
    std::cout << "(" << x << ", " << y << ", " << z << ")";
}

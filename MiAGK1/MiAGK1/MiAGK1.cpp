#include "Buffer.h"

int main()
{
    int width = 264;
    int height = 264;

    Buffer buffer(width, height);
    buffer.SetSize(width, height);
    buffer.ClearColor(0xFF00FFFF); // 0x A R G B
    
    Buffer depthBuffer(width, height);
    depthBuffer.ClearDepthBuffer();

    float4 color1({ 1.0f, 0.0f, 0.0f, 1.0f });
    float4 color2({ 0.0f, 1.0f, 0.0f, 1.0f });
    float4 color3({ 0.0f, 0.0f, 1.0f, 1.0f });

    buffer.Triangle({0.0f, 0.9f, -1.0f}, {1.0f, 0.9f, 0.0f}, {0.5f, -0.5f, 0.0f},
                    {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, depthBuffer);
    buffer.Triangle({-0.5f, 0.9f, 0.0f }, { 0.8f, 0.0f, -1.0f }, { 0.3f, 0.0f, 1.0f },
                    { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, depthBuffer);

    float4x4 testMatrix(1.0f,  2.0f,  3.0f,  4.0f,
                        5.0f,  6.0f,  7.0f,  8.0f,
                        9.0f,  10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f);
    testMatrix.WriteToConsole(); // Correct

    float3 smallFloat({ 1.0f, 2.0f, 3.0f });

    float3 result = smallFloat * testMatrix;
    result.WriteToConsole(); // Correct


    buffer.Save();
}
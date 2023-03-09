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

    buffer.Save();
}
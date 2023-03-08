#include "Buffer.h"

int main()
{
    Buffer buffer(264, 264);
    buffer.SetSize(264, 264);
    buffer.ClearColor(0xFF00FFFF); // 0x A R G B

    float4 color1({ 1.0f, 0.0f, 0.0f, 1.0f });
    float4 color2({ 0.0f, 1.0f, 0.0f, 1.0f });
    float4 color3({ 0.0f, 0.0f, 1.0f, 1.0f });

    buffer.Triangle({0.0f, 0.9f}, {2.2f, 0.9f}, {0.0f, 0.0f},
                    {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f});

    buffer.Save();
}
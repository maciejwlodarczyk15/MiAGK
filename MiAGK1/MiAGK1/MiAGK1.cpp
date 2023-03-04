#include "Buffer.h"

int main()
{
    Buffer buffer(264, 264);
    buffer.SetSize(264, 264);
    buffer.ClearColor(0xFF00FFFF); // 0x A R G B

    //buffer.ColorHalf({ -1.0f, -1.0f }, { 1.0f, 1.0f }, 0xFFFF0000);

    buffer.Triangle({-0.5f, 1.0f}, {1.0f, 1.0f}, {-1.0f, -1.0f}, 0xFFFF0000);

    buffer.Save();
}
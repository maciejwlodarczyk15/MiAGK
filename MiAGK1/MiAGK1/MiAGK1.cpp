#include "Buffer.h"

int main()
{
    Buffer buffer(264, 264);
    buffer.SetSize(264, 264);
    buffer.ClearColor(0xFF00FFFF); // 0x A R G B

    buffer.Triangle({ 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f });

    buffer.Save();
}

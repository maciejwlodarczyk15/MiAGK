#include "Buffer.h"

int main()
{
    Buffer buffer(264, 264);
    buffer.SetSize(1920, 1080);
    buffer.ClearColor(0xFF00FFFF); // 0x A R G B
    buffer.Save();
}

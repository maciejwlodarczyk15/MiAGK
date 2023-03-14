#include "Buffer.h"
#define M_PI 3.14159265358979323846

int main()
{
    // Screen settings
    int width = 264;
    int height = 264;

    // Projection matrix
    float4x4 projectionMatrix;
    float fov = 90.0f; // field of view
    float aspectRatio = (float)width / height;
    float near = 0.01f;
    float far = 10000.0f;

    float f = tanf((fov * 0.5f) * (M_PI / 180.0f));

    projectionMatrix.m[0][0] = 1 / (f * aspectRatio);
    projectionMatrix.m[1][1] = 1 / f;
    projectionMatrix.m[2][2] = (far + near) / (near - far);
    projectionMatrix.m[2][3] = 1;
    projectionMatrix.m[3][2] = (2.0f * far * near) / (near - far);
    projectionMatrix.m[3][3] = 0;

    // Setting up buffer
    Buffer buffer(width, height);
    //buffer.SetSize(width, height); size can be changed
    buffer.ClearColor(0xFF00FFFF); // 0x A R G B
    
    // Depth buffer
    Buffer depthBuffer(width, height);
    depthBuffer.ClearDepthBuffer();

    // Colors (red, green, blue)
    float4 color1( 1.0f, 0.0f, 0.0f, 1.0f );
    float4 color2( 0.0f, 1.0f, 0.0f, 1.0f );
    float4 color3( 0.0f, 0.0f, 1.0f, 1.0f );

    // Triangles
    buffer.Triangle({ 0.0f, 0.9f, -1.0f }, { 1.0f, 0.9f, 0.0f }, { 0.5f, -0.5f, 0.0f },
                    { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, depthBuffer, projectionMatrix);
    buffer.Triangle({ -0.5f, 0.9f, 0.0f }, { 0.8f, 0.0f, -1.0f }, { 0.3f, 0.0f, 1.0f },
                    { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, depthBuffer, projectionMatrix);

    buffer.Save();
}
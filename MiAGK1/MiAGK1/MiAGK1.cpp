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
    float near = 0.1f;
    float far = 100.0f;

    float f = tan((fov * 0.5f) * (M_PI / 180.0f));

    projectionMatrix.m[0][0] = 1 / (f * aspectRatio);
    projectionMatrix.m[1][1] = 1 / f;
    projectionMatrix.m[2][2] = (far + near) / (near - far);
    projectionMatrix.m[2][3] = -1;
    projectionMatrix.m[3][2] = (2.0f * far * near) / (near - far);
    projectionMatrix.m[3][3] = 0;

    projectionMatrix.WriteToConsole(); // Correct

    // Setting up buffer
    Buffer buffer(width, height);
    //buffer.SetSize(width, height); size can be changed
    buffer.ClearColor(0xFF00FFFF); // 0x A R G B
    
    // Depth buffer
    Buffer depthBuffer(width, height);
    depthBuffer.ClearDepthBuffer();

    // Colors (red, green, blue)
    float4 color1({ 1.0f, 0.0f, 0.0f, 1.0f });
    float4 color2({ 0.0f, 1.0f, 0.0f, 1.0f });
    float4 color3({ 0.0f, 0.0f, 1.0f, 1.0f });

    // Triangles
    buffer.Triangle({ 0.0f, 0.5f, 0.0f }, { 0.5f, 1.0f, 0.0f }, { 1.0f, 0.5f, 0.0f },
                    color1, color2, color3, depthBuffer, projectionMatrix);
    buffer.Triangle({-0.5f, 0.9f, 0.0f }, { 0.8f, 0.0f, -1.0f }, { 0.3f, 0.0f, 1.0f },
                    color1, color2, color3, depthBuffer, projectionMatrix);
    


    // Checking matrixes
    float4x4 testMatrix(1.0f,  2.0f,  3.0f,  4.0f,
                        5.0f,  6.0f,  7.0f,  8.0f,
                        9.0f,  10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f);
    testMatrix.WriteToConsole(); // Correct

    float3 smallFloat({ 1.0f, 2.0f, 3.0f });

    float3 result = smallFloat * testMatrix;
    result.WriteToConsole(); // Correct

    float4x4 testMatrix2(16.0f, 15.0f, 14.0f, 13.0f,
                         12.0f, 11.0f, 10.0f, 9.0f,
                         8.0f,  7.0f,  6.0f,  5.0f,
                         4.0f,  3.0f,  2.0f,  1.0f);

    float4x4 lul = testMatrix * testMatrix2;
    lul.WriteToConsole(); // Correct

    float4 testxd({ 1.0f, 2.0f, 3.0f, 4.0f });
    float4 result2 = testxd * testMatrix;
    result2.WriteToConsole(); // Correct

    buffer.Save();
}
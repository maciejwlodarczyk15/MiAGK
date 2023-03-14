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

    projectionMatrix.m[2][3] = -1;
    projectionMatrix.m[3][2] = (2.0f * far * near) / (near - far);

    //projectionMatrix.m[2][3] = (2.0f * far * near) / (near - far);
    //projectionMatrix.m[3][2] = -1;

    projectionMatrix.m[3][3] = 0;

    projectionMatrix.WriteToConsole();

    // Camera
    float3 eye(0.0f, 0.0f, 20.0f);      // position of camer
    float3 center(0.0f, 0.0f, 0.0f);    // target
    float3 upVec(0.0f, 1.0f, 0.0f);     // up vector


    float3 zAxis = (center - eye);      // Z-Axis
    zAxis.Normalize();
    upVec.Normalize();
    float3 xAxis = zAxis.Cross(upVec);  // X-Axis
    float3 yAxis = xAxis.Cross(zAxis);  // Z-Axis

    float4x4 camMatrix;
    camMatrix.Identity();

    camMatrix.m[0][0] = xAxis.x;
    camMatrix.m[0][1] = xAxis.y;
    camMatrix.m[0][2] = xAxis.z;
    camMatrix.m[0][3] = -xAxis.Dot(eye);
    camMatrix.m[1][0] = yAxis.x;
    camMatrix.m[1][1] = yAxis.y;
    camMatrix.m[1][2] = yAxis.z;
    camMatrix.m[1][3] = -yAxis.Dot(eye);
    camMatrix.m[2][0] = xAxis.x;
    camMatrix.m[2][1] = xAxis.y;
    camMatrix.m[2][2] = xAxis.z;
    camMatrix.m[2][3] = -xAxis.Dot(eye);

    //camMatrix.WriteToConsole();

    // Setting up buffer
    Buffer buffer(width, height);
    // buffer.SetSize(width, height); size can be changed
    buffer.ClearColor(0xFF00FFFF); // 0x A R G B
    
    // Depth buffer
    Buffer depthBuffer(width, height);
    depthBuffer.ClearDepthBuffer();

    // Colors (red, green, blue)
    float4 color1( 1.0f, 0.0f, 0.0f, 1.0f );
    float4 color2( 0.0f, 1.0f, 0.0f, 1.0f );
    float4 color3( 0.0f, 0.0f, 1.0f, 1.0f );

    // Triangles
    buffer.Triangle({ 0.0f, 0.9f, -3.0f }, { 1.0f, 0.9f, -3.0f }, { 0.5f, -0.5f, -3.0f },
                    { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, depthBuffer, projectionMatrix);
    //buffer.Triangle({ -0.5f, 0.9f, -1.0f }, { 0.8f, 0.0f, -1.0f }, { 0.3f, 0.0f, 1.0f },
    //                { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, depthBuffer, projectionMatrix);

    buffer.Save();
}
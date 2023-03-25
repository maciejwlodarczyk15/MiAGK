#include "Buffer.h"
#define M_PI 3.14159265358979323846

int main()
{
    // Screen settings
    int width = 1000;
    int height = 1000;

    // Projection matrix
    float4x4 projectionMatrix;         // View to projection
    float fov = 60.0f; // field of view
    float aspectRatio = (float)width / height;
    float near = 0.1f;
    float far = 100.0f;

    float f = tanf((fov * 0.5f) * (M_PI / 180.0f));

    projectionMatrix.m[0][0] = 1 / (f * aspectRatio);
    projectionMatrix.m[1][1] = 1 / f;
    projectionMatrix.m[2][2] = (far + near) / (near - far);

    projectionMatrix.m[3][2] = -1;
    projectionMatrix.m[2][3] = (2.0f * far * near) / (near - far);

    projectionMatrix.m[3][3] = 0;

    // Camera
    float3 eye(0.0f, 0.0f, 3.0f);       // position of camera
    float3 center(0.0f, 0.0f, 0.0f);    // target
    float3 upVec(0.0f, -1.0f, 0.0f);    // up vector


    float3 zAxis = (center - eye);      // Z-Axis
    zAxis.Normalize();
    upVec.Normalize();
    float3 xAxis = zAxis.Cross(upVec);  // X-Axis
    float3 yAxis = xAxis.Cross(zAxis);  // Y-Axis
    
    std::cout << "\nX:";
    xAxis.WriteToConsole();
    std::cout << "\nY:";
    yAxis.WriteToConsole();
    std::cout << "\nZ:";
    zAxis.WriteToConsole();

    float4x4 camMatrix;                 // World To View
    camMatrix = camMatrix.Identity();

    camMatrix.m[0][0] = xAxis.x;
    camMatrix.m[0][1] = xAxis.y;
    camMatrix.m[0][2] = xAxis.z;
    camMatrix.m[0][3] = -xAxis.Dot(eye);
    camMatrix.m[1][0] = yAxis.x;
    camMatrix.m[1][1] = yAxis.y;
    camMatrix.m[1][2] = yAxis.z;
    camMatrix.m[1][3] = -yAxis.Dot(eye);
    camMatrix.m[2][0] = -zAxis.x;
    camMatrix.m[2][1] = -zAxis.y;
    camMatrix.m[2][2] = -zAxis.z;
    camMatrix.m[2][3] = -zAxis.Dot(eye);

    std::cout << "Camera matrix\n";
    camMatrix.WriteToConsole();


    float4x4 modelMatrix;               // Model to world
    modelMatrix = modelMatrix.Identity();


    float3 translation(0.0f, 0.0f, -1.0f);
    modelMatrix = modelMatrix * modelMatrix.multByTanslation(translation);

    float angle = 0;
    float3 axis(0.0f, 0.0f, 1.0f);
    modelMatrix = modelMatrix * modelMatrix.multByRotation(angle, axis);

    float3 scale(1.0f, 1.0f, 1.0f);
    modelMatrix = modelMatrix * modelMatrix.multByScale(scale);
    

    float4x4 mvp;
    std::cout << "\nProjection:\n";
    projectionMatrix.WriteToConsole();
    std::cout << "\n\nCam:\n";
    camMatrix.WriteToConsole();
    std::cout << "\n\nModel:\n";
    modelMatrix.WriteToConsole();
    mvp = projectionMatrix * camMatrix * modelMatrix;
    mvp.WriteToConsole();


    // Setting up buffer
    Buffer buffer(width, height);
    buffer.ClearColor(0xFF236F92); // 0x A R G B
    
    // Depth buffer
    Buffer depthBuffer(width, height);
    depthBuffer.ClearDepthBuffer();

    // Colors (red, green, blue)
    float4 color1( 1.0f, 0.0f, 0.0f, 1.0f );
    float4 color2( 0.0f, 1.0f, 0.0f, 1.0f );
    float4 color3( 0.0f, 0.0f, 1.0f, 1.0f );

    // Triangles
    buffer.Triangle({ 0.5f, 0.7f, -0.5f }, { 1.0f, 0.0f, 0.5f }, { 0.3f, 0.5f, -0.5f },
                    color1, color2, color3, depthBuffer, mvp);

    buffer.Triangle({ 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
        color1, color2, color3, depthBuffer, mvp);

    buffer.Save();
}
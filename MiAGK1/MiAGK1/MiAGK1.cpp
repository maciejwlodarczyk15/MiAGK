#include "Buffer.h"
#include "SimpleTriangle.h"
#include "SimpleSphere.h"
#include "SimpleCone.h"
#include "DirectionalLight.h"

#define M_PI 3.14159265358979323846

int main()
{
    // Screen settings
    int width = 1000;
    int height = 1000;

    // Projection matrix
    float4x4 projectionMatrix;          // View to projection
    float fov = 60.0f;                  // Field of view
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
    float3 eye(0.0f, 0.0f, 3.0f);       // Position of camera
    float3 center(0.0f, 0.0f, 0.0f);    // Target
    float3 upVec(0.0f, -1.0f, 0.0f);    // Up vector (reversed??)


    float3 zAxis = (center - eye);      // Z-Axis
    zAxis.Normalize();
    upVec.Normalize();
    float3 xAxis = zAxis.Cross(upVec);  // X-Axis
    float3 yAxis = xAxis.Cross(zAxis);  // Y-Axis

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

    float4x4 modelMatrix;               // Model to world
    modelMatrix = modelMatrix.Identity();


    float3 translation(0.0f, 0.0f, -1.0f);
    modelMatrix = modelMatrix * modelMatrix.multByTanslation(translation);

    float angle = 0;
    float3 axis(0.0f, 0.0f, 1.0f);
    modelMatrix = modelMatrix * modelMatrix.multByRotation(angle, axis);

    float3 scale(1.0f, 1.0f, 1.0f);
    modelMatrix = modelMatrix * modelMatrix.multByScale(scale);
    
    float4x4 mvp;                       // Model - View - Projection
    mvp = projectionMatrix * camMatrix * modelMatrix;

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
    DirectionalLight light(float3(0.0f, 0.0f, 1.0f), float3(1.0f, 1.0f, 1.0f));

    SimpleTriangle triangle({ 0.5f, 0.7f, -0.5f }, { 1.0f, 0.0f, 0.5f }, { 0.3f, 0.5f, -0.5f }, 
                            color1, color2, color3);
    triangle.Draw(buffer, depthBuffer, mvp, light);

    float4x4 modelMatrix2;               
    modelMatrix2 = modelMatrix.Identity();


    float3 translation2(0.0f, 0.0f, 5.0f);
    modelMatrix2 = modelMatrix2 * modelMatrix2.multByTanslation(translation2);

    float angle2 = -45;
    float3 axis2(1.0f, 0.0f, 0.0f);
    modelMatrix2 = modelMatrix2 * modelMatrix2.multByRotation(angle2, axis2);

    float3 scale2(1.0f, 1.0f, 1.0f);
    modelMatrix2 = modelMatrix2 * modelMatrix2.multByScale(scale2);

    float4x4 mvp2;                       // Model - View - Projection
    mvp2 = projectionMatrix * camMatrix * modelMatrix2;

   // Triangle(v1, v2, v3, c1, c2, c3)
   SimpleTriangle triangle2({ 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
                           color1, color2, color3);
   
   triangle2.Draw(buffer, depthBuffer, mvp2, light);
   
   // Cone(pos, radius, height, vertices at base)
   SimpleCone cone1(float3(0.0f, 1.0f, 0.0f), 1.0f, 4.0f, 20);
   cone1.Draw(buffer, depthBuffer, mvp2, color1, light);
   
   // Sphere(pos, radius, vert slices, horiz slices)
   SimpleSphere sphere1(float3(-3.0f, 0.0f, 0.0f), 1.2f, 12, 8);
   sphere1.Draw(buffer, depthBuffer, mvp2, light);

    buffer.Save();
    buffer.Display();
}
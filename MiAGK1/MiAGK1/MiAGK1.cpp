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
    
    // Setting up buffer
    Buffer buffer(width, height);
    buffer.ClearColor(0xFF000000); // 0x A R G B
    
    // Depth buffer
    Buffer depthBuffer(width, height);
    depthBuffer.ClearDepthBuffer();

    Buffer textureBuffer1(width, height);
    textureBuffer1.Load("earth.tga");
    
    Buffer textureBuffer2(width, height);
    textureBuffer2.Load("earth.tga");

    // Colors (red, green, blue)
    float4 color1( 1.0f, 0.0f, 0.0f, 1.0f );
    float4 color2( 0.0f, 1.0f, 0.0f, 1.0f );
    float4 color3( 0.0f, 0.0f, 1.0f, 1.0f );
    
    // Triangles
    DirectionalLight light(float3(-1.0f, 0.0f, 0.0f), float3(1.0f, 1.0f, 1.0f), float3(1.0f, 1.0f, 1.0f));
    PointLight pLight1(float3(-2.0f, 5.0f, 5.0f), float3(0.5f, 0.5f, 0.5f), float3(1.0f, 1.0f, 1.0f), 1.0f, 250.0f, 1.0f, 0.14f, 0.07f);
    
    
    float4x4 s1modelMatrix;               // Model to world
    s1modelMatrix = s1modelMatrix.Identity();
    
    float3 s1translation(0.0f, 0.0f, 0.0f);
    s1modelMatrix = s1modelMatrix * s1modelMatrix.multByTanslation(s1translation);
    
    float s1angle = 0;
    float3 s1axis(0.0f, 0.0f, 1.0f);
    s1modelMatrix = s1modelMatrix * s1modelMatrix.multByRotation(s1angle, s1axis);
    
    float3 s1scale(1.0f, 1.0f, 1.0f);
    s1modelMatrix = s1modelMatrix * s1modelMatrix.multByScale(s1scale);
    
    float4x4 s1mvp;                       // Model - View - Projection
    s1mvp = projectionMatrix * camMatrix * s1modelMatrix;
    
    SimpleSphere s1(float3(3.0f, 3.0f, 5.0f), 1.0f, 16, 16);
    s1.Draw(buffer, depthBuffer, s1mvp, light, s1modelMatrix, pLight1, eye, center, textureBuffer1);
    
    
    
    float4x4 c1modelMatrix;
    c1modelMatrix = c1modelMatrix.Identity();
    
    float3 c1translation(0.0f, 0.0f, 0.0f);
    c1modelMatrix = c1modelMatrix * c1modelMatrix.multByTanslation(c1translation);
    
    float c1angle = 135;
    float3 c1axis(0.0f, 0.0f, 1.0f);
    c1modelMatrix = c1modelMatrix * c1modelMatrix.multByRotation(c1angle, c1axis);
    
    float c1angle2 = 45;
    float3 c1axis2(1.0f, 0.0f, 0.0f);
    c1modelMatrix = c1modelMatrix * c1modelMatrix.multByRotation(c1angle2, c1axis2);
    
    float3 c1scale(1.0f, 1.0f, 1.0f);
    c1modelMatrix = c1modelMatrix * c1modelMatrix.multByScale(c1scale);
    
    float4x4 c1mvp;
    c1mvp = projectionMatrix * camMatrix * c1modelMatrix;
    
    SimpleCone c1(float3(0.0f, 0.0f, 0.0f), 0.3f, 1, 16);
    c1.Draw(buffer, depthBuffer, c1mvp, light, c1modelMatrix, pLight1, eye, center, textureBuffer2);
    
    float4x4 s2modelMatrix;
    s2modelMatrix = s2modelMatrix.Identity();
    
    float3 s2translation(0.0f, 0.0f, 0.0f);
    s2modelMatrix = s2modelMatrix * s2modelMatrix.multByTanslation(s2translation);
    
    float s2angle = 0;
    float3 s2axis(0.0f, 0.0f, 1.0f);
    s2modelMatrix = s2modelMatrix * s2modelMatrix.multByRotation(s2angle, s2axis);
    
    float s2angle2 = 45;
    float3 s2axis2(1.0f, 0.0f, 0.0f);
    s2modelMatrix = s2modelMatrix * s2modelMatrix.multByRotation(s2angle2, s2axis2);
    
    float3 s2scale(1.0f, 1.0f, 1.0f);
    s2modelMatrix = s2modelMatrix * s2modelMatrix.multByScale(s2scale);
    
    float4x4 s2mvp;
    s2mvp = projectionMatrix * camMatrix * s2modelMatrix;
     
    SimpleSphere s2(float3(-2.0f, 2.0f, 5.0f), 1.0f, 16, 16);
    s2.Draw(buffer, depthBuffer, s2mvp, light, s2modelMatrix, pLight1, eye, center, textureBuffer2);


    buffer.Save(); 
    buffer.Display();
}
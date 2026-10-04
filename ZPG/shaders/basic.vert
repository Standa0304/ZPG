#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

uniform vec3 translation;
uniform vec3 scale;
uniform float rotationY;

void main()
{
    float x = position.x * scale.x;
    float y = position.y * scale.y;
    float z = position.z * scale.z;

    float rotatedX = cos(rotationY) * x + sin(rotationY) * z;

    float rotatedY = y;

    float rotatedZ = -sin(rotationY) * x + cos(rotationY) * z;

    float finalX = rotatedX + translation.x;
    float finalY = rotatedY + translation.y;
    float finalZ = rotatedZ + translation.z;

    vertexColor = color;

    gl_Position = vec4(finalX, finalY, finalZ, 1.0);
}
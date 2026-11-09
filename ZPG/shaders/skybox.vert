#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    TexCoords = aPos;

    mat4 view = mat4(mat3(viewMatrix));

    gl_Position = projectionMatrix * view * vec4(aPos, 1.0);
}
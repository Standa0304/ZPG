
#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

uniform float ambientStrength;

void main()
{
    vec3 Color = vec3(0.6, 0.6, 0.6);
    vec3 ambient = ambientStrength * Color;

    FragColor = vec4(ambient, 1.0);
}

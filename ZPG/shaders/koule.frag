#version 330 core

out vec4 FragColor;

void main()
{
    vec3 Color = vec3(1.0, 0.9, 0.0);

    FragColor = vec4(Color, 1.0);
}
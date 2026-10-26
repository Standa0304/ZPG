#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 vertexColor;

out vec4 FragColor;

uniform vec3 lightPosition;

void main()
{
    vec3 objectColor = vertexColor;;

    vec3 normal = normalize(worldNormal);
    vec3 lightDirection = normalize(lightPosition - worldPosition);

    float diffuseStrength = max(dot(normal, lightDirection), 0.0);

    vec3 result = objectColor * diffuseStrength;

    FragColor = vec4(result, 1.0);
}

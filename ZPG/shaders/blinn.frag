#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;

out vec4 FragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;

uniform vec3 viewPosition;

void main()
{
    vec3 objectColor = vec3(0.6, 0.6, 0.6);

    vec3 normal = normalize(worldNormal);

    vec3 lightDirection = normalize(lightPosition - worldPosition);

    vec3 viewDirection = normalize(viewPosition - worldPosition);

    vec3 ambient = ambientStrength * lightColor * objectColor;

    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diffuseStrength * diff * lightColor * objectColor;

    vec3 halfwayDirection = normalize(lightDirection + viewDirection);

    float spec = pow(
        max(dot(normal, halfwayDirection), 0.0),
        32.0
    );

    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

out vec3 worldPosition;	
out vec3 worldNormal;
out vec3 vertexColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void){
    vertexColor = color;
    vec4 pos = modelMatrix * vec4(position,1.0f);
    worldPosition = pos.xyz/pos.w;
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    worldNormal = normalize(normalMatrix * normal);
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(position,1.0f);
}
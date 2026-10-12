#pragma once

#include <glad/gl.h>
#include "Shader.h"
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/ext/matrix_float4x4.hpp>

class Camera;
class ShaderProgram
{
private:
    GLuint programID;
    Camera* m_camera;

public:
    ShaderProgram(Shader& vertexShader, Shader& fragmentShader);

    void use();

    GLuint getID() const;

    void setUniform(const char* name, float value);
    void setUniform(const char* name, int value);
    void setUniform(const char* name, glm::vec3 value);
    void setUniform(const char* name, glm::vec4 value);
    void setUniform(const char* name, glm::mat4 value);
    ~ShaderProgram();
};
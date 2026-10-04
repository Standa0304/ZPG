#pragma once

#include <glad/gl.h>
#include "Shader.h"
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class ShaderProgram
{
private:
    GLuint programID;

public:
    ShaderProgram(Shader& vertexShader, Shader& fragmentShader);

    void use();

    GLuint getID() const;

    void setUniform(const char* name, float value);
    void setUniform(const char* name, int value);
    void setUniform(const char* name, glm::vec3 value);
    void setUniform(const char* name, glm::vec4 value);

    ~ShaderProgram();
};
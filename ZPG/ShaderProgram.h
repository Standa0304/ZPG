#pragma once

#include <glad/gl.h>
#include "Shader.h"
#include <iostream>

class ShaderProgram
{
private:
    GLuint programID;

public:
    ShaderProgram(Shader& vertexShader, Shader& fragmentShader);

    void use();

    GLuint getID() const;

    ~ShaderProgram();
};
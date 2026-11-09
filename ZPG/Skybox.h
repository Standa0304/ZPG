#pragma once

#include <glad/gl.h>
#include <string>

#include "Texture.h"
#include "ShaderProgram.h"

class Skybox
{
private:
    GLuint VAO;
    GLuint VBO;

    Texture* texture;
    ShaderProgram* shaderProgram;

public:
    Skybox(
        const std::string& right,
        const std::string& left,
        const std::string& top,
        const std::string& bottom,
        const std::string& back,
        const std::string& front,
        ShaderProgram* shaderProgram
    );

    ~Skybox();

    void draw();
};
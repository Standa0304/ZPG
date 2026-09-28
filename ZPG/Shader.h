#pragma once

#include <glad/gl.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
private:
    GLuint shaderID;

public:
    Shader(GLenum shaderType, const char* shaderFile);

    GLuint getID() const;

    ~Shader();
};
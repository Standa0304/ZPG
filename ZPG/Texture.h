#pragma once

#include <glad/gl.h>
#include <string>

class Texture
{
private:
    GLuint textureID;
    GLenum textureType;

public:
    Texture(const std::string& path);

    Texture(
        const std::string& right,
        const std::string& left,
        const std::string& top,
        const std::string& bottom,
        const std::string& back,
        const std::string& front
    );

    ~Texture();

    void bind(GLuint textureUnit);
    void unbind();
};
#pragma once
#include <cstddef>
#include <glad/gl.h>

class Model{
private:
    GLuint VBO;
    GLuint VAO;

    size_t vertexCount;
    size_t stride;

public:
    Model(float* vertices, size_t size, size_t stride);
    void draw();
    ~Model();
};
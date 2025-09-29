#pragma once
#include <GL/glew.h>

class Model {
private:
    GLuint VBO, VAO;
    size_t vertexCount;
    size_t stride;

public:
    Model(float* vertices, size_t size, size_t count, size_t stride);
    void draw();
    ~Model();
};

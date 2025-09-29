#pragma once
#include <GL/glew.h>
#include <iostream>

class Shader {
private:
    GLuint vertexID, fragmentID;
    GLuint programID;
    const char* vertexSource;
    const char* fragmentSource;

public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    void compile();
    void use() { glUseProgram(programID); }
    GLuint getProgramID() const { return programID; }
    ~Shader();
};

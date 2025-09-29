#include "Shader.h"

Shader::Shader(const char* vertexSrc, const char* fragmentSrc)
    : vertexSource(vertexSrc), fragmentSource(fragmentSrc), programID(0) {
}

void Shader::compile() {
    GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vertexSource, nullptr);
    glCompileShader(vertexID);

    GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentID);

    programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

Shader::~Shader() {
    if (programID) glDeleteProgram(programID);
}

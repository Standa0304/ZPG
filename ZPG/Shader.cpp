#include "Shader.h"

Shader::Shader(GLenum shaderType, const char* shaderFile)
{
    shaderID = glCreateShader(shaderType);

    if (shaderID == 0)
    {
        std::cout << "Unable to create shader." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ifstream file(shaderFile);

    if (!file.is_open())
    {
        std::cout << "Unable to open shader file: "
                  << shaderFile << std::endl;

        glDeleteShader(shaderID);
        exit(EXIT_FAILURE);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string shaderCode = buffer.str();

    const char* source = shaderCode.c_str();

    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[1024];

        glGetShaderInfoLog(
            shaderID,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cout << "Shader compilation failed:"
                  << std::endl;

        std::cout << infoLog << std::endl;

        glDeleteShader(shaderID);
        exit(EXIT_FAILURE);
    }
}

GLuint Shader::getID() const
{
    return shaderID;
}

Shader::~Shader()
{
    glDeleteShader(shaderID);
}
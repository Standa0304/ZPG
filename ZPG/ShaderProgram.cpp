#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(
    Shader& vertexShader,
    Shader& fragmentShader)
{
    programID = glCreateProgram();

    if (programID == 0)
    {
        std::cout << "Unable to create shader program."
                  << std::endl;

        exit(EXIT_FAILURE);
    }

    glAttachShader(programID, vertexShader.getID());
    glAttachShader(programID, fragmentShader.getID());

    glLinkProgram(programID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[1024];

        glGetProgramInfoLog(
            programID,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cout << "Shader program linking failed:"
                  << std::endl;

        std::cout << infoLog << std::endl;

        glDeleteProgram(programID);
        exit(EXIT_FAILURE);
    }
}

void ShaderProgram::use()
{
    glUseProgram(programID);
}

GLuint ShaderProgram::getID() const
{
    return programID;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(programID);
}
#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
#include "Camera.h"

ShaderProgram::ShaderProgram(Shader& vertexShader, Shader& fragmentShader)
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

        glGetProgramInfoLog(programID, sizeof(infoLog), nullptr, infoLog);

        std::cout << "Shader program linking failed:" << std::endl;

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

void ShaderProgram::setUniform(const char* name, float value)
{
    GLint location = glGetUniformLocation(programID, name);

    if (location == -1)
    {
        std::cout << "Uniform variable not found: " << name << std::endl;
        return;
    }

    glUniform1f(location, value);
}

void ShaderProgram::setUniform(const char* name, int value)
{
    GLint location = glGetUniformLocation(programID, name);

    if (location == -1)
    {
        std::cout << "Uniform variable not found: " << name << std::endl;
        return;
    }

    glUniform1i(location, value);
}


void ShaderProgram::setUniform(const char* name, glm::vec3 value)
{
    GLint location = glGetUniformLocation(programID, name);

    if (location == -1)
    {
        std::cout << "Uniform variable not found: " << name << std::endl;
        return;
    }

    glUniform3f(
        location,
        value.x,
        value.y,
        value.z
    );
}

void ShaderProgram::setUniform(const char* name, glm::vec4 value)
{
    GLint location = glGetUniformLocation(programID, name);

    if (location == -1)
    {
        std::cout << "Uniform variable not found: " << name << std::endl;
        return;
    }

    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::setUniform(const char* name, glm::mat4 value)
{
    GLint modelMatrixLocation = glGetUniformLocation(programID, name);

    if (modelMatrixLocation == -1)
    {
        std::cout << "Uniform variable not found: " << name << std::endl;
        return;
    }

    glUniformMatrix4fv(modelMatrixLocation,1,GL_FALSE,glm::value_ptr(value));
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(programID);
}
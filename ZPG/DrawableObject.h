#pragma once

#include "Model.h"
#include "ShaderProgram.h"

#include <glm/glm.hpp>

class DrawableObject
{
private:
    Model* model;
    ShaderProgram* shaderProgram;

    glm::mat4 modelMatrix;

public:
    DrawableObject(Model* model, ShaderProgram* shaderProgram, glm::vec3 position, glm::vec3 scale, float rotationY);

    void draw();
};
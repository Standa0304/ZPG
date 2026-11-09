#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include <glm/glm.hpp>

class DrawableObject
{
private:
    Model* model;
    ShaderProgram* shaderProgram;
    Texture* texture;

    glm::mat4 modelMatrix;

public:
    DrawableObject(Model* model, ShaderProgram* shaderProgram, glm::vec3 position, glm::vec3 scale, float rotationY, Texture* texture);

    void draw();
    
    void setModelMatrix(glm::mat4 matrix);
};
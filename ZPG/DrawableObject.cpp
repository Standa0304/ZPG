#include "DrawableObject.h"

#include <glm/gtc/matrix_transform.hpp>

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram,glm::vec3 position, glm::vec3 scale, float rotationY, Texture* texture)
{
    this->model = model;
    this->shaderProgram = shaderProgram;
    this->texture = texture;

    modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, position);

    modelMatrix = glm::rotate(modelMatrix, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));

    modelMatrix = glm::scale(modelMatrix, scale);
}

void DrawableObject::draw()
{
    shaderProgram->use();

    if (texture != nullptr)
    {
        texture->bind(0);
        shaderProgram->setUniform("textureUnitID", 0);
    }


    shaderProgram->setUniform("modelMatrix", modelMatrix);

    model->draw();
}


void DrawableObject::setModelMatrix(glm::mat4 matrix)
{
    modelMatrix = matrix;
}

#include "Transformation.h"

Transformation::Transformation()
{
    matrix = glm::mat4(1.0f);
}

void Transformation::translate(glm::vec3 position)
{
    matrix = glm::translate(matrix, position);
}

void Transformation::rotate(float angle, glm::vec3 axis)
{
    matrix = glm::rotate(matrix, angle, axis);
}

void Transformation::scale(glm::vec3 size)
{
    matrix = glm::scale(matrix, size);
}

glm::mat4 Transformation::getMatrix() const
{
    return matrix;
}

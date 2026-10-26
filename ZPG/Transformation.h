#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformation
{
private:
    glm::mat4 matrix;

public:
    Transformation();

    void translate(glm::vec3 position);
    void rotate(float angle, glm::vec3 axis);
    void scale(glm::vec3 size);

    glm::mat4 getMatrix() const;
};

#pragma once

#include "DrawableObject.h"

#include <glm/vec3.hpp>

#include <vector>

class Scene
{
private:
    std::vector<DrawableObject*> objects;

public:
    Scene();
    ~Scene();

    void addObject(Model* model, ShaderProgram* ShaderProgram, glm::vec3 position, glm::vec3 scale, float rotationY);

    void draw(ShaderProgram& shader);
};
#pragma once

#include "Model.h"
#include "ShaderProgram.h"

#include <glm/vec3.hpp>

#include <vector>

struct SceneObject
{
    Model* model;

    glm::vec3 position;
    glm::vec3 scale;
    float rotationY;
};


class Scene
{
private:
    std::vector<Model*> models;
    std::vector<SceneObject> objects;

public:
    Scene();
    ~Scene();

    Model* addModel(float* vertices, size_t size, size_t stride);

    void addObject(
        Model* model,
        glm::vec3 position,
        glm::vec3 scale,
        float rotationY
    );

    void draw(ShaderProgram& shader);
};
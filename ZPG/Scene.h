#pragma once

#include "DrawableObject.h"

#include <glm/vec3.hpp>

#include <vector>
#include "Skybox.h"

class Scene
{
private:
    std::vector<DrawableObject*> objects;

public:
    Scene();
    ~Scene();

    DrawableObject*  addObject(Model* model, ShaderProgram* ShaderProgram, glm::vec3 position, glm::vec3 scale, float rotationY, Texture* texture = nullptr);

    void draw();

    Skybox* skybox = nullptr;

    void setSkybox(Skybox* skybox);
    Skybox* getSkybox();

};
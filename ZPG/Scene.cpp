#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    for (Model* model : models)
    {
        delete model;
    }
}

Model* Scene::addModel(float* vertices, size_t size, size_t stride)
{
    Model* model = new Model(vertices, size, stride);

    models.push_back(model);

    return model;
}

void Scene::addObject(
    Model* model,
    glm::vec3 position,
    glm::vec3 scale,
    float rotationY
)
{
    SceneObject object;

    object.model = model;
    object.position = position;
    object.scale = scale;
    object.rotationY = rotationY;

    objects.push_back(object);
}

void Scene::draw(ShaderProgram& program)
{
    for (SceneObject& object : objects)
    {
        program.setUniform("translation", object.position);
        program.setUniform("scale", object.scale);
        program.setUniform("rotationY", object.rotationY);

        object.model->draw();
    }
}
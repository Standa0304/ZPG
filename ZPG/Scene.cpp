    #include "Scene.h"

    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
        for (DrawableObject* object : objects)
        {
            delete object;
        }

    }

    DrawableObject* Scene::addObject(Model* model, ShaderProgram* shaderProgram, glm::vec3 position, glm::vec3 scale, float rotationY)
    {
        DrawableObject* object = new DrawableObject(model, shaderProgram, position, scale, rotationY);

        objects.push_back(object);

        return object;
    }

    void Scene::draw()
    {
        for (DrawableObject* object : objects)
        {
            object->draw();
        }
    }
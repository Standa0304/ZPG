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

    DrawableObject* Scene::addObject(Model* model, ShaderProgram* shaderProgram, glm::vec3 position, glm::vec3 scale, float rotationY, Texture* texture)
    {
        DrawableObject* object = new DrawableObject(model, shaderProgram, position, scale, rotationY, texture);

        objects.push_back(object);

        return object;
    }

    void Scene::draw()
    {
        if (skybox != nullptr)
        {
            skybox->draw();
        }
        
        for (DrawableObject* object : objects)
        {
            object->draw();
        }
    }

    void Scene::setSkybox(Skybox* skybox)
    {
        this->skybox = skybox;
    }

    Skybox* Scene::getSkybox()
    {
        return skybox;
    }
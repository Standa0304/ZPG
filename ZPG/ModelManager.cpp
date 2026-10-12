#include "ModelManager.h"

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
    for (Model* model : models)
    {
        delete model;
    }
}

Model* ModelManager::addModel(float* vertices, size_t size, size_t stride)
{
    Model* model = new Model(vertices, size, stride);

    models.push_back(model);

    return model;
}
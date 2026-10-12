#pragma once

#include "Model.h"

#include <vector>

class ModelManager
{
private:
    std::vector<Model*> models;

public:
    ModelManager();
    ~ModelManager();

    Model* addModel(float* vertices, size_t size, size_t stride);
};
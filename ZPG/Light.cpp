#include "Light.h"

Light::Light()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    color = glm::vec3(1.0f, 1.0f, 1.0f);

    ambientStrength = 0.2f;
    diffuseStrength = 1.0f;
    specularStrength = 0.5f;

    constantAttenuation = 1.0f;
    linearAttenuation = 0.09f;
    quadraticAttenuation = 0.032f;
}

glm::vec3 Light::getPosition() const
{
    return position;
}

glm::vec3 Light::getColor() const
{
    return color;
}

float Light::getAmbientStrength() const
{
    return ambientStrength;
}

float Light::getDiffuseStrength() const
{
    return diffuseStrength;
}

float Light::getSpecularStrength() const
{
    return specularStrength;
}

void Light::setPosition(glm::vec3 position)
{
    this->position = position;
}

float Light::getConstantAttenuation() const
{
    return constantAttenuation;
}

float Light::getLinearAttenuation() const
{
    return linearAttenuation;
}

float Light::getQuadraticAttenuation() const
{
    return quadraticAttenuation;
}

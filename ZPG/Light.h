#pragma once

#include <glm/vec3.hpp>

class Light
{
public:
    Light();

    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;

    float getAmbientStrength() const;
    float getDiffuseStrength() const;
    float getSpecularStrength() const;

    float getConstantAttenuation() const;
    float getLinearAttenuation() const;
    float getQuadraticAttenuation() const;

    void setPosition(glm::vec3 position);

private:
    glm::vec3 position;
    glm::vec3 color;

    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    float ambientStrength;
    float diffuseStrength;
    float specularStrength;
};

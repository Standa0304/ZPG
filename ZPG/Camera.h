#pragma once

#include <glm/glm.hpp>

class ShaderProgram;
class Camera
{
  private:
    ShaderProgram* shaderProgram;
    
    glm::vec3 position;
    float yaw;
    float pitch;

  public:
    Camera(ShaderProgram* shaderProgram);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;
    glm::vec3 getPosition() const;

    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);

    void rotate(float xOffset, float yOffset);

};
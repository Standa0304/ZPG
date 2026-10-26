
#include "Camera.h"
#include "ShaderProgram.h"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera(ShaderProgram* shaderProgram)
{
    this->shaderProgram = shaderProgram;

    position = glm::vec3(0.0f, 1.5f, 5.0f);
    yaw = -90.0f;
    pitch = 0.0f;
}

glm::mat4 Camera::getViewMatrix() const
{
    glm::vec3 front;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);

    return glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const
{
    return glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 200.0f);
}

void Camera::moveForward(float deltaTime)
{
    glm::vec3 front;

    front.x = cos(glm::radians(yaw));
    front.y = 0.0f;
    front.z = sin(glm::radians(yaw));

    front = glm::normalize(front);
    position += front * 3.0f * deltaTime;
}

void Camera::moveBackward(float deltaTime)
{
    glm::vec3 front;

    front.x = cos(glm::radians(yaw));
    front.y = 0.0f;
    front.z = sin(glm::radians(yaw));

    front = glm::normalize(front);
    position -= front * 3.0f * deltaTime;
}

void Camera::moveLeft(float deltaTime)
{
    glm::vec3 front;

    front.x = cos(glm::radians(yaw));
    front.y = 0.0f;
    front.z = sin(glm::radians(yaw));

    front = glm::normalize(front);

    glm::vec3 right = glm::normalize(
        glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))
    );

    position -= right * 3.0f * deltaTime;
}

void Camera::moveRight(float deltaTime)
{
    glm::vec3 front;

    front.x = cos(glm::radians(yaw));
    front.y = 0.0f;
    front.z = sin(glm::radians(yaw));

    front = glm::normalize(front);

    glm::vec3 right = glm::normalize(
        glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))
    );

    position += right * 3.0f * deltaTime;
}

void Camera::rotate(float xOffset, float yOffset)
{
    float sensitivity = 0.1f;

    yaw += xOffset * sensitivity;
    pitch += yOffset * sensitivity;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }

    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
}

glm::vec3 Camera::getPosition() const
{
    return position;
}
#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "DrawableObject.h"
#include "Scene.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include "ModelManager.h"
#include "Camera.h"
#include "Light.h"

class Application {
public:
    Application();
    ~Application();

    void initialization();
    void createShaders();
    void createScenes();
    void run();

private:
    GLFWwindow* window;
    ShaderProgram* normalProgram;
    ShaderProgram* blueProgram;
    ShaderProgram* ambientProgram;
    ShaderProgram* lambertProgram;
    ShaderProgram* phongProgram;
    ShaderProgram* blinnProgram;
    ModelManager modelManager;
    Camera* camera;
    Light* light;
    DrawableObject* earthObject;
    DrawableObject* moonObject;

    bool rightMousePressed;
    double lastMouseX;
    double lastMouseY;
    float lastFrameTime;

    Scene scene1;
    Scene scene2;
    Scene scene3;
    Scene scene4;

    Scene* currentScene;

    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void window_focus_callback(GLFWwindow* window, int focused);
    static void window_iconify_callback(GLFWwindow* window, int iconified);
    static void window_size_callback(GLFWwindow* window, int width, int height);
    static void cursor_callback(GLFWwindow* window, double x, double y);
    static void button_callback(GLFWwindow* window, int button, int action, int mods);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

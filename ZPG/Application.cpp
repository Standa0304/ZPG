#include "Application.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "models/sphere.h"
#include "models/gift.h"
#include "models/tree.h"
#include "models/bushes.h"
#include "models/triangle.h"
#include <cstdlib>
#include <ctime>
#include "models/login.h"
#include "models/sun.h"

Application::Application() : window(nullptr), normalProgram(nullptr), blueProgram(nullptr), currentScene(nullptr){}
Application::~Application() {
    delete normalProgram;
    delete blueProgram;
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initialization() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) { exit(EXIT_FAILURE); }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "ERROR: could not create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        printf("GLAD initialization failed\n");

        glfwTerminate();
        exit(EXIT_FAILURE);
    }


    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, button_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

void Application::createShaders()
{

    Shader* vertexShader =
        new Shader(GL_VERTEX_SHADER, "shaders/basic.vert");

    Shader* fragmentShader =
        new Shader(GL_FRAGMENT_SHADER, "shaders/basic.frag");

    Shader* blueFragmentShader =
        new Shader(GL_FRAGMENT_SHADER, "shaders/blue.frag");

    normalProgram =
        new ShaderProgram(*vertexShader, *fragmentShader);

    blueProgram =
        new ShaderProgram(*vertexShader, *blueFragmentShader);

    delete vertexShader;
    delete fragmentShader;
    delete blueFragmentShader;

}


void Application::createScenes()
{

    Model* triangleModel = modelManager.addModel((float*)triangle, sizeof(triangle), 6);

    scene1.addObject(triangleModel, normalProgram, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.7f), 0.0f);

    Model* sphereModel = modelManager.addModel((float*)sphere, sizeof(sphere), 6);

    scene2.addObject(sphereModel, normalProgram, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), 0.0f);


    Model* treeModel = modelManager.addModel((float*)tree, sizeof(tree), 6);

    Model* bushModel = modelManager.addModel((float*)bushes, sizeof(bushes), 6);

    for (int i = 0; i < 20; i++)
    {
        int randomX = -80 + rand() % 161;
        int randomZ = -80 + rand() % 161;
        int randomScale = 20 + rand() % 81;

        float randX = randomX / 100;
        float randZ = randomZ / 100;
        float randScale = randomScale / 100;
        float rotation = 0;
        scene3.addObject(treeModel, normalProgram, glm::vec3(randX, 0.0f, randZ), glm::vec3(randScale), rotation);
    }

    for (int i = 0; i < 30; i++)
    {
        float x = -0.8f + (float)rand() / RAND_MAX * 1.6f;
        float z = -0.8f + (float)rand() / RAND_MAX * 1.6f;

        float scale = 0.15f + (float)rand() / RAND_MAX * 0.20f;
        float rotation = (float)rand() / RAND_MAX * 6.28318f;

        scene3.addObject(bushModel, normalProgram, glm::vec3(x, -0.3f, z), glm::vec3(scale), rotation);
    }

     Model* loginModel = modelManager.addModel((float*)loginVertices, sizeof(loginVertices), 6);

    scene4.addObject(loginModel, normalProgram,  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0.6f);

    currentScene = &scene1;
}

void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(-0.5f, 0.0f, -1.0f));
    M = glm::rotate(M, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        if (currentScene != nullptr)
        {
            normalProgram->use();
            currentScene->draw(*normalProgram);
        }

    
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
    
    if (action == GLFW_PRESS)
    {
        Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));

        if (key == GLFW_KEY_1)
        {
            application->currentScene = &application->scene1;
        }

        if (key == GLFW_KEY_2)
        {
            application->currentScene = &application->scene2;
        }

        if (key == GLFW_KEY_3)
        {
            application->currentScene = &application->scene3;
        }

        if (key == GLFW_KEY_4)
        {
            application->currentScene = &application->scene4;
        }
    }

    printf("key_callback [%d,%d,%d,%d]\n", key, scancode, action, mods);
}
void Application::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback\n"); }

void Application::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback\n"); }

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
    printf("resize %d,%d\n", width, height);
    glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback\n"); }

void Application::button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mods);
}

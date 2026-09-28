#include "Application.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "models/sphere.h"
#include "models/gift.h"

Application::Application() : window(nullptr), normalProgram(nullptr), blueProgram(nullptr), plainModel(nullptr), secondModel(nullptr){}
Application::~Application() {
    delete normalProgram;
    delete blueProgram;
    delete plainModel;
    delete secondModel;
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

void Application::createModels() {
    
    plainModel = new Model((float*)sphere, sizeof(sphere), 6);

    secondModel = new Model((float*)gift, sizeof(gift), 6);
}

void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      //  glm::mat4 M = glm::mat4(1.0f);
   //     M = glm::translate(M, glm::vec3(-0.5f, 0.0f, -1.0f));
   //     M = glm::rotate(M, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 M = glm::mat4(1.0f);
        M = glm::scale(M, glm::vec3(0.3f));
        M = glm::rotate(M, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

        normalProgram->use();
        plainModel->draw();

        glClear(GL_DEPTH_BUFFER_BIT); 
        
        blueProgram->use();
        secondModel->draw();
    
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);
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

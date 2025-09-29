#include "Application.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

Application::Application() : window(nullptr), shaderSquare(nullptr), shaderTriangle(nullptr), square(nullptr), triangle(nullptr) {}
Application::~Application() {
    delete shaderSquare;
    delete shaderTriangle;
    delete square;
    delete triangle;
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initialization() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) { exit(EXIT_FAILURE); }

    window = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "ERROR: could not create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    glewInit();

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

void Application::createShaders() {
    const char* vertex_shader =
        "#version 330 core\n"
        "layout(location = 0) in vec3 vp;\n"
        "layout(location = 1) in vec3 normal;\n"
        "uniform mat4 modelMatrix;\n"
        "out vec3 fragNormal;\n"
        "void main() {\n"
        "    fragNormal = normal;\n"
        "    gl_Position = modelMatrix * vec4(vp, 1.0);\n"
        "}";

    const char* fragment_shader =
        "#version 330 core\n"
        "in vec3 fragNormal;\n"
        "out vec4 frag_colour;\n"
        "void main() {\n"
        "    frag_colour = vec4(normalize(fragNormal) * 0.5 + 0.5, 1.0);\n"
        "}";

    shaderSquare = new Shader(vertex_shader, fragment_shader);
    shaderSquare->compile();
}

void Application::createModels() {
    float squareVertices[] = {
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };



    square = new Model(squareVertices, sizeof(squareVertices), 6, 6);
}

void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shaderSquare->use();
        glm::mat4 M = glm::mat4(1.0f);
        glm::translate(M, glm::vec3(-0.5f, 0.0f, -1.0f));
        M = glm::rotate(M, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));


        GLint loc = glGetUniformLocation(shaderSquare->getProgramID(), "modelMatrix");
        if (loc != -1)
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(M));
        square->draw();
    
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

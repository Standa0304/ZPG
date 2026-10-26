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
    #include "models/plain.h"
    #include "models/clock.h"
    #include "models/earth.h"
    #include "models/moon.h"
    #include "models/rocket.h"


    Application::Application() : window(nullptr), earthObject(nullptr), moonObject(nullptr), ambientProgram(nullptr), lambertProgram(nullptr), phongProgram(nullptr), blinnProgram(nullptr), normalProgram(nullptr), blueProgram(nullptr), camera(nullptr), light(nullptr), rightMousePressed(false), lastMouseX(0.0), lastMouseY(0.0), lastFrameTime(0.0f), currentScene(nullptr){}
    Application::~Application() {
        delete camera;
        delete light;
        delete normalProgram;
        delete blueProgram;
        delete ambientProgram;
        delete lambertProgram; 
        delete phongProgram; 
        delete blinnProgram; 
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
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
    }

    void Application::createShaders()
    {

        Shader* vertexShader =
            new Shader(GL_VERTEX_SHADER, "shaders/basic.vert");

        Shader* lightVertexShader =
            new Shader(GL_VERTEX_SHADER, "shaders/light.vert");

        Shader* clockvertexShader =
            new Shader(GL_VERTEX_SHADER, "shaders/clock.vert");

        Shader* fragmentShader =
            new Shader(GL_FRAGMENT_SHADER, "shaders/basic.frag");

        Shader* ambientFragmentShader =
            new Shader(GL_FRAGMENT_SHADER, "shaders/ambient.frag");

        Shader* lambertFragmentShader =
            new Shader(GL_FRAGMENT_SHADER, "shaders/lambert.frag");

        Shader* phongFragmentShader =
            new Shader(GL_FRAGMENT_SHADER, "shaders/phong.frag");

        Shader* blinnFragmentShader =
            new Shader(GL_FRAGMENT_SHADER, "shaders/blinn.frag");

        Shader* blueFragmentShader =
            new Shader(GL_FRAGMENT_SHADER, "shaders/blue.frag");

        normalProgram = new ShaderProgram(*vertexShader, *fragmentShader);

        blueProgram = new ShaderProgram(*clockvertexShader, *blueFragmentShader);

        ambientProgram = new ShaderProgram(*lightVertexShader, *ambientFragmentShader);

        lambertProgram = new ShaderProgram(*lightVertexShader, *lambertFragmentShader);

        phongProgram = new ShaderProgram(*lightVertexShader, *phongFragmentShader);

        blinnProgram = new ShaderProgram(*lightVertexShader, *blinnFragmentShader);

        delete vertexShader;
        delete fragmentShader;
        delete blueFragmentShader;
        delete clockvertexShader;
        delete ambientFragmentShader;
        delete phongFragmentShader;
        delete lambertFragmentShader;
        delete blinnFragmentShader;
        delete lightVertexShader;

        camera = new Camera(normalProgram);

        ambientProgram->use();
        ambientProgram->setUniform("ambientStrength", 0.8f);

        light = new Light();
        lambertProgram->setLight(light);
        phongProgram->setLight(light);
        blinnProgram->setLight(light);

        normalProgram->setCamera(camera);
        blueProgram->setCamera(camera);
        ambientProgram->setCamera(camera);
        lambertProgram->setCamera(camera);
        phongProgram->setCamera(camera);
        blinnProgram->setCamera(camera);

    }


    void Application::createScenes()
    {
        Model* plainModel = modelManager.addModel((float*)plain, sizeof(plain), 6);

        Model* clockObjectModel = modelManager.addModel((float*)clockModel, sizeof(clockModel), 9);

        Model* sphereModel = modelManager.addModel((float*)sphere, sizeof(sphere), 6);

        scene2.addObject(sphereModel, phongProgram, glm::vec3(-1.5f, 0.0f, 0.0f), glm::vec3(0.5f), 0.0f);
        scene2.addObject(sphereModel, phongProgram, glm::vec3( 1.5f, 0.0f, 0.0f), glm::vec3(0.5f), 0.0f);
        scene2.addObject(sphereModel, phongProgram, glm::vec3(0.0f,  0.0f, -1.5f), glm::vec3(0.5f), 0.0f);
        scene2.addObject(sphereModel, phongProgram, glm::vec3(0.0f,  0.0f,  1.5f), glm::vec3(0.5f), 0.0f);

        Model* sunModel = modelManager.addModel((float*)sun, sizeof(sun), 9);
        Model* earthModel = modelManager.addModel((float*)earth, sizeof(earth), 9);
        Model* moonModel = modelManager.addModel((float*)moon, sizeof(moon), 9);
        Model* rocketModel = modelManager.addModel((float*)rocket, sizeof(rocket), 9);

        earthObject = scene1.addObject(earthModel, phongProgram, glm::vec3(2.5f, 0.0f, 0.0f), glm::vec3(0.2f), 0.0f);
        moonObject = scene1.addObject(moonModel, phongProgram, glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.05f), 0.0f);
        scene1.addObject(sunModel, normalProgram, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f), 0.0f);
        scene1.addObject(rocketModel, lambertProgram, glm::vec3(3.2f, 0.0f, 0.0f), glm::vec3(0.1f), glm::radians(70.0f));
        Model* treeModel = modelManager.addModel((float*)tree, sizeof(tree), 6);

        Model* bushModel = modelManager.addModel((float*)bushes, sizeof(bushes), 6);

        for (int i = 0; i < 80; i++)
        {
            int randomX = -800 + rand() % 1601;
            int randomZ = -800 + rand() % 1601;
            int randomScale = 10 + rand() % 71;

            float randX = randomX / 100.0f;
            float randZ = randomZ / 100.0f;
            float randScale = randomScale / 100.0f;

            scene3.addObject(treeModel, phongProgram, glm::vec3(randX, 0.0f, randZ), glm::vec3(randScale), 0.0f);
        }

        for (int i = 0; i < 80; i++)
        {
            int randomX = -800 + rand() % 1601;
            int randomZ = -800 + rand() % 1601;
            int randomScale = 40 + rand() % 21;

            float randX = randomX / 100.0f;
            float randZ = randomZ / 100.0f;
            float randScale = randomScale / 100.0f;

            scene3.addObject(bushModel, phongProgram, glm::dvec3(randX, 0.0f, randZ), glm::vec3(randScale), 0.0f);
        }
        scene3.addObject(plainModel, normalProgram, glm::vec3(0.0f, -0.05f, 0.0f), glm::vec3(20.0f, 1.0f, 20.0f), 0.0f);

        scene3.addObject(clockObjectModel, blueProgram, glm::vec3(3.0f, 1.0f, 2.0f), glm::vec3(0.2f, 0.2f, -0.2f), 0.0f);

        Model* loginModel = modelManager.addModel((float*)loginVertices, sizeof(loginVertices), 6);

        scene4.addObject(loginModel, normalProgram,  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0.6f);

        currentScene = &scene1;
    }

    void Application::run() {

        lastFrameTime = (float)glfwGetTime();

        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = (float)glfwGetTime();
            float deltaTime = currentFrame - lastFrameTime;
            lastFrameTime = currentFrame;

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                camera->moveForward(deltaTime);
            }

            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                camera->moveBackward(deltaTime);
            }

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                camera->moveLeft(deltaTime);
            }

            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                camera->moveRight(deltaTime);
            }

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 M = glm::mat4(1.0f);
        M = glm::translate(M, glm::vec3(-0.5f, 0.0f, -1.0f));
        M = glm::rotate(M, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        if (currentScene != nullptr)
            {
                int width;
                int height;

                glfwGetFramebufferSize(window, &width, &height);

                if (height > 0)
                {
                    float aspectRatio = (float)width / (float)height;

                    normalProgram->updateCamera(aspectRatio);
                    blueProgram->updateCamera(aspectRatio);
                    ambientProgram->updateCamera(aspectRatio);
                    lambertProgram->updateCamera(aspectRatio);
                    phongProgram->updateCamera(aspectRatio);
                    blinnProgram->updateCamera(aspectRatio);

                    if (currentScene == &scene1){
                        float time = (float)glfwGetTime();

                        float earthSpeed = time * 1.0f;
                        float earthSpeedAxis = time * 0.2f;
                        float moonSpeed = time * 0.2f;


                        glm::mat4 earthMatrix(1.0f);

                        earthMatrix = glm::rotate(earthMatrix, earthSpeed, glm::vec3(0.0f, 1.0f, 0.0f));

                        earthMatrix = glm::translate(earthMatrix, glm::vec3(4.0f, 0.0f, 0.0f));

                        earthMatrix = glm::rotate(earthMatrix, earthSpeedAxis, glm::vec3(0.0f, 1.0f, 0.0f));

                        earthMatrix = glm::scale(earthMatrix, glm::vec3(0.4f));


                        glm::mat4 moonMatrix(1.0f);

                        moonMatrix = glm::rotate(moonMatrix, earthSpeed, glm::vec3(0.0f, 1.0f, 0.0f));

                        moonMatrix = glm::translate(moonMatrix, glm::vec3(4.0f, 0.0f, 0.0f));

                        moonMatrix = glm::rotate(moonMatrix, moonSpeed, glm::vec3(0.0f, 1.0f, 0.0f));

                        moonMatrix = glm::translate(moonMatrix, glm::vec3(0.5f, 0.0f, 0.0f));

                        moonMatrix = glm::scale(moonMatrix, glm::vec3(0.1f));

                        earthObject->setModelMatrix(earthMatrix);
                        moonObject->setModelMatrix(moonMatrix);

                        currentScene->draw();

                    }
                    else
                    {
                        currentScene->draw();
                    }
                }
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
    }
    void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height){
        glViewport(0, 0, width, height);

            printf("Framebuffer: %d x %d\n", width, height);
    }

    void Application::cursor_callback(GLFWwindow* window, double x, double y) { 
        Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));

        if (!application->rightMousePressed)
        {
            return;
        }

        float xOffset = (float)(x - application->lastMouseX);
        float yOffset = (float)(application->lastMouseY - y);

        application->lastMouseX = x;
        application->lastMouseY = y;

        application->camera->rotate(xOffset, yOffset);
        printf("cursor_callback\n"); 
    }

    void Application::button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        Application* application =
            static_cast<Application*>(glfwGetWindowUserPointer(window));

        if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            if (action == GLFW_PRESS)
            {
                application->rightMousePressed = true;

                glfwGetCursorPos(
                    window,
                    &application->lastMouseX,
                    &application->lastMouseY
                );
            }

            if (action == GLFW_RELEASE)
            {
                application->rightMousePressed = false;
            }
        }
    }
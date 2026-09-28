#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include "Application.h"

int main(void)
{
    Application* app = new Application();

    app->initialization();
    app->createShaders();
    app->createModels();
    app->run();

    delete app;

    return 0;
}
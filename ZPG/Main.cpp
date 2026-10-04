#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include "Application.h"

int main(void)
{
    Application app;

    app.initialization();
    app.createShaders();
    app.createScenes();
    app.run();

    return 0;
}
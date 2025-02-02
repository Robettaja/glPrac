#include "Time.hpp"
#include <GLFW/glfw3.h>

float Time::lastTime;
float Time::time;
float Time::deltaTime;

void Time::UpdateTime()
{
    float time = glfwGetTime();
    deltaTime = time - lastTime;
    lastTime = time;
}

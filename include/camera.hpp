#pragma once

#include "shader.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera
{
  private:
    glm::vec3 camForward;
    bool firstClick;
    double lastX, lastY;
    double yaw, pitch;

  public:
    glm::vec3 position;
    glm::vec3 orientation;
    glm::vec3 camRight, camUp;
    float sensitivity, speed;
    glm::mat4 projection;
    glm::mat4 view;
    Camera(glm::vec3 position, float width, float height);
    void UpdateAndSendMatricies(Shader& shader, float width, float height);
    void MoveCamera(GLFWwindow* window);
    void RotateCamera(GLFWwindow* window);
};

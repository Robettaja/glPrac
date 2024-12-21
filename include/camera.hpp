#pragma once
#include "shader.h"
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
  private:
    glm::vec3 camForward;
    float width, height;
    bool firstClick;
    double lastX, lastY;
    double yaw, pitch;

  public:
    glm::vec3 cameraPos;
    glm::vec3 orientation;
    glm::vec3 camRight, camUp;
    float sensitivity, speed;
    glm::mat4 projection;
    glm::mat4 view;
    Camera(glm::vec3 position, float width, float height);
    void UpdateAndSendMatricies(Shader& shader);
    void MoveCamera(GLFWwindow* window);
    void RotateCamera(GLFWwindow* window);
};

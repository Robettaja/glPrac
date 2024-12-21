#include "camera.hpp"
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>

Camera::Camera(glm::vec3 position, float width, float height)
{
    cameraPos = position;
    Orientation = glm::vec3(0, 0, -1);
    camUp = glm::vec3(0, 1, 0);
    camRight = glm::normalize(glm::cross(Orientation, camUp));

    this->width = width;
    this->height = height;

    projection = glm::mat4(1.0f);
    view = glm::mat4(1.0f);

    speed = 0.25f;
    sensitivity = 0.15f;

    pitch = 0.0f;
    yaw = -90.0f;

    lastX = width / 2;
    lastY = height / 2;
    firstClick = true;
}
void Camera::UpdateAndSendMatricies(Shader& shader)
{
    projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
    view = glm::lookAt(cameraPos, cameraPos + Orientation, camUp);

    glm::mat4 projectionView = projection * view;
    shader.setMat4("projectionView", projectionView);
}
void Camera::MoveCamera(GLFWwindow* window)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        if (firstClick)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwGetCursorPos(window, &lastX, &lastY);
            firstClick = false;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            cameraPos += Orientation * speed;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {

            cameraPos -= Orientation * speed;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            cameraPos += camRight * speed;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            cameraPos -= camRight * speed;
        }
        RotateCamera(window);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}
void Camera::RotateCamera(GLFWwindow* window)
{

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    double deltaX = mouseX - lastX;
    double deltaY = lastY - mouseY;

    lastX = mouseX;
    lastY = mouseY;

    deltaX = deltaX * sensitivity;
    deltaY = deltaY * sensitivity;

    yaw += deltaX;
    pitch += deltaY;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    Orientation.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    Orientation.y = sin(glm::radians(pitch));
    Orientation.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Orientation = glm::normalize(Orientation);
    camRight = glm::normalize(glm::cross(Orientation, camUp));
}

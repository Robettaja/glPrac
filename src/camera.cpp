#include "camera.hpp"
#include "time.hpp"

#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera(glm::vec3 position, int width, int height)
    : position(position), orientation(glm::vec3(0, 0, -1)), camRight(glm::normalize(glm::cross(orientation, camUp))),
      camUp(glm::vec3(0, 1, 0)), sensitivity(0.08f), speed(60.0f), projection(glm::mat4(1.0f)), view(glm::mat4(1.0f)),
      firstClick(true), lastX(static_cast<float>(width) / 2), lastY(static_cast<float>(height) / 2), yaw(-90.0f),
      pitch(0.0f)
{
}

void Camera::UpdateMatrices(const Shader& shader, const int width, const int height)
{
    projection =
        glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
    view = glm::lookAt(position, position + orientation, camUp);

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
            position += orientation * speed * Time::deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            position -= orientation * speed * Time::deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            position += camRight * speed * Time::deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            position -= camRight * speed * Time::deltaTime;
        }
        RotateCamera(window);
    }
    else
    {
        if (!firstClick)
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

    orientation.x = static_cast<float>(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
    orientation.y = static_cast<float>(sin(glm::radians(pitch)));
    orientation.z = static_cast<float>(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
    orientation = glm::normalize(orientation);
    camRight = glm::normalize(glm::cross(orientation, camUp));
}

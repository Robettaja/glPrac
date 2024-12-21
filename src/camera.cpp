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

    speed = 0.01f;
    sensitivity = 0.01f;

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
            glfwSetCursorPos(window, width / 2, height / 2);
            firstClick = true;
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
        firstClick = true;
        lastX = width / 2;
        lastX = height / 2;
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

    float angleX = deltaX * sensitivity;
    float angleY = deltaY * sensitivity;

    glm::mat4 rotationX = glm::rotate(glm::mat4(1), angleY, glm::vec3(1, 0, 0));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1), -angleX, glm::vec3(0, 1, 0));

    glm::vec4 rotatedVec = (rotationY * rotationX) * glm::vec4(Orientation, 1);

    Orientation.x = rotatedVec.x;
    Orientation.y = rotatedVec.y;
    Orientation.z = rotatedVec.z;
}

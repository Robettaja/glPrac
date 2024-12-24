#include <glad/glad.h>

#include "block.hpp"
#include "shader.hpp"
#include "camera.hpp"

#include <cstddef>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <vector>

int winWidth = 800;
int winHeight = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    winWidth = width;
    winHeight = height;
    glViewport(0, 0, width, height);
}
int main()
{
    // We initialize glfw so we can use it
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window for application check if it exist and asing it to the
    // software
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "OpenGL Harjoitus", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Check if glad was succesfully assigned to program
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Camera cam(glm::vec3(0, 0, 3), winWidth, winHeight);

    Shader shader("shaders/vertex.vert", "shaders/fragment.frag");

    std::vector<Block*> blocks;
    int size = 16;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            for (size_t k = 0; k < size; k++)
            {
                Block* block = new Block(glm::vec3(i * 2, j * 2, k * 2));
                blocks.emplace_back(block);
            }
        }
    }

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.UpdateAndSendMatricies(shader, winWidth, winHeight);
        cam.MoveCamera(window);

        for (size_t i = 0; i < blocks.size(); i++)
        {
            blocks[i]->Draw(shader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    for (size_t i = 0; i < blocks.size(); i++)
    {
        delete blocks[i];
    }
    glfwTerminate();
    return 0;
}

#include <glad/glad.h>

#include "shader.hpp"
#include "chunk.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "modelLoader.hpp"
#include "vertex.hpp"

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
    if (!glfwInit())
    {
        const char* description;
        int error = glfwGetError(&description);
        std::cout << "Error: " << error << " Description: " << description << std::endl;
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window for application check if it exist and asing it to the
    // software
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "OpenGL Harjoitus", NULL, NULL);
    if (window == NULL)
    {
        const char* description;
        int error = glfwGetError(&description);
        std::cout << "Error: " << error << " Description: " << description << std::endl;
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Check if glad was succesfully assigned to program
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glm::vec3 lightPos(3.0f, 3.0f, 0.0f);
    Camera cam(glm::vec3(0, 0, 3), winWidth, winHeight);

    Shader shader("shaders/vertex.vert", "shaders/fragment.frag");
    shader.setVec3("lightPos", lightPos);

    std::vector<Texture> textures;
    textures.emplace_back("textures/grass.jpg");
    Chunk chunk(glm::vec3(0, 0, -20));
    chunk.CreateMesh();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.UpdateAndSendMatricies(shader, winWidth, winHeight);
        cam.MoveCamera(window);
        chunk.Render(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

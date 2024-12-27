#include <glad/glad.h>

#include "shader.hpp"
#include "chunk.hpp"
#include "camera.hpp"
#include "renderer.hpp"

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

    std::vector<Vertex> vertices{
        // Main side
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(0.5f, -0.5f, 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(0.5f, 0.5f, 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, 1))},
        // Bottom side
        Vertex{glm::vec3(0.5f, -0.5f, 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, -1, 0))},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, -1, 0))},
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, -1, 0))},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, -1, 0))},
        // Back Side
        Vertex{glm::vec3(0.5f, -0.5f, -0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, -1))},
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, -1))},
        Vertex{glm::vec3(0.5f, 0.5f, -0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, -1))},
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, -1))},
        // Top Side
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 1, 0))},
        Vertex{glm::vec3(0.5f, 0.5f, 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 1, 0))},
        Vertex{glm::vec3(0.5f, 0.5f, -0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 1, 0))},
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 1, 0))},
        // Left Side
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(-1, 0, 0))},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(-1, 0, 0))},
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(-1, 0, 0))},
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(-1, 0, 0))},
        // Right Side
        Vertex{glm::vec3(0.5f, -0.5f, 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(1, 0, 0))},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(1, 0, 0))},
        Vertex{glm::vec3(0.5f, 0.5f, -0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(1, 0, 0))},
        Vertex{glm::vec3(0.5f, 0.5f, 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(1, 0, 0))},

    };
    std::vector<unsigned int> indices{
        // Main side
        0, 1, 2, //
        2, 3, 0, //
        // Bottom side
        4, 5, 6, //
        6, 7, 4, //
        // Back Side
        8, 9, 10,  //
        10, 11, 8, //
        // Top Side
        12, 13, 14, //
        14, 15, 12, //
        // Left Side
        16, 17, 18, //
        18, 19, 16, //
        // Right Side
        20, 21, 22, //
        22, 23, 20, //

    };
    std::vector<Texture> textures;
    textures.emplace_back("textures/stone.jpg");
    Renderer renderer(vertices, indices, textures, glm::vec3(0.0f, 0.0f, 0.0f));

    Renderer renderer2(vertices, indices, textures, glm::vec3(1.0f, 0.0f, 0.0f));

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.UpdateAndSendMatricies(shader, winWidth, winHeight);
        cam.MoveCamera(window);
        renderer.Draw(shader);
        renderer2.Draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

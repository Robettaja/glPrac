#include <glad/glad.h>

#include "shader.hpp"
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

std::vector<Vertex> generatePyramidVertices()
{
    std::vector<Vertex> vertices;

    // Define the positions of the pyramid
    glm::vec3 apex(0.0f, 1.0f, 0.0f);    // Top point
    glm::vec3 base0(-0.5f, 0.0f, -0.5f); // Bottom-left of the base
    glm::vec3 base1(0.5f, 0.0f, -0.5f);  // Bottom-right of the base
    glm::vec3 base2(0.5f, 0.0f, 0.5f);   // Top-right of the base
    glm::vec3 base3(-0.5f, 0.0f, 0.5f);  // Top-left of the base

    // Normals for each face
    glm::vec3 normalFront = glm::normalize(glm::vec3(0.0f, 0.5f, -0.5f));
    glm::vec3 normalRight = glm::normalize(glm::vec3(0.5f, 0.5f, 0.0f));
    glm::vec3 normalBack = glm::normalize(glm::vec3(0.0f, 0.5f, 0.5f));
    glm::vec3 normalLeft = glm::normalize(glm::vec3(-0.5f, 0.5f, 0.0f));
    glm::vec3 normalBottom(0.0f, -1.0f, 0.0f);

    // UV coordinates for each vertex
    glm::vec2 uvApex(0.5f, 1.0f);
    glm::vec2 uvBase0(0.0f, 0.0f);
    glm::vec2 uvBase1(1.0f, 0.0f);
    glm::vec2 uvBase2(1.0f, 1.0f);
    glm::vec2 uvBase3(0.0f, 1.0f);

    // Front face (apex, base0, base1)
    vertices.push_back({apex, uvApex, normalFront});
    vertices.push_back({base0, uvBase0, normalFront});
    vertices.push_back({base1, uvBase1, normalFront});

    // Right face (apex, base1, base2)
    vertices.push_back({apex, uvApex, normalRight});
    vertices.push_back({base1, uvBase0, normalRight});
    vertices.push_back({base2, uvBase1, normalRight});

    // Back face (apex, base2, base3)
    vertices.push_back({apex, uvApex, normalBack});
    vertices.push_back({base2, uvBase0, normalBack});
    vertices.push_back({base3, uvBase1, normalBack});

    // Left face (apex, base3, base0)
    vertices.push_back({apex, uvApex, normalLeft});
    vertices.push_back({base3, uvBase0, normalLeft});
    vertices.push_back({base0, uvBase1, normalLeft});

    // Bottom face (base0, base1, base2, base3)
    vertices.push_back({base0, uvBase0, normalBottom});
    vertices.push_back({base1, uvBase1, normalBottom});
    vertices.push_back({base2, uvBase2, normalBottom});
    vertices.push_back({base0, uvBase0, normalBottom});
    vertices.push_back({base2, uvBase2, normalBottom});
    vertices.push_back({base3, uvBase3, normalBottom});

    return vertices;
}

std::vector<unsigned int> generatePyramidIndices()
{
    std::vector<unsigned int> indices;

    // Front face
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    // Right face
    indices.push_back(3);
    indices.push_back(4);
    indices.push_back(5);

    // Back face
    indices.push_back(6);
    indices.push_back(7);
    indices.push_back(8);

    // Left face
    indices.push_back(9);
    indices.push_back(10);
    indices.push_back(11);

    // Bottom face
    indices.push_back(12);
    indices.push_back(13);
    indices.push_back(14);
    indices.push_back(15);
    indices.push_back(16);
    indices.push_back(17);

    return indices;
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

    std::vector<Vertex> vertices = generatePyramidVertices();
    std::vector<unsigned int> indices = generatePyramidIndices();
    std::vector<Texture> textures;
    textures.emplace_back("textures/stone.jpg");
    Renderer renderer(vertices, indices, textures);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.UpdateAndSendMatricies(shader, winWidth, winHeight);
        cam.MoveCamera(window);

        renderer.Draw(shader, glm::vec3(0.0f, 0.0f, 0.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

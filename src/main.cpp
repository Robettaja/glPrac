#include <future>
#include <glad/glad.h>

#include "chunkmanager.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "chunk.hpp"
#include "camera.hpp"
#include "logger.hpp"
#include "time.hpp"

#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm/detail/qualifier.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int winWidth = 800;
int winHeight = 600;
void init_imgui(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void shutdown_imgui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void update_imgui()
{
    // Begin Imgui Render
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Imgui Widget Code Here
    ImGui::Text("FPS: %d", (int)(1.0f / Time::deltaTime));

    // Finish Imgui Render
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)winWidth, (float)winHeight);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
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
    logger::init();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window for application check if it exists and assign it to the
    // software
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "OpenGL Harjoitus", nullptr, nullptr);
    if (window == nullptr)
    {
        const char* description;
        int error = glfwGetError(&description);
        std::cout << "Error: " << error << " Description: " << description << std::endl;
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Check if glad was successfully assigned to program
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    init_imgui(window);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glm::vec3 lightPos(Chunk::CHUNK_SIZE / 2, 9.0f, Chunk::CHUNK_SIZE / 2);
    Camera cam(glm::vec3(0, 0, 3), winWidth, winHeight);

    Shader shader("shaders/vertex.vert", "shaders/fragment.frag");
    shader.setVec3("lightPos", lightPos);

    Texture texture("textures/grass.jpg");
    texture.Bind();
    ChunkManager manager(shader, cam);

    manager.CreateChunks();
    while (!glfwWindowShouldClose(window))
    {
        Time::UpdateTime();
        glClearColor(.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.UpdateMatrices(shader, winWidth, winHeight);
        cam.MoveCamera(window);
        manager.Update();
        update_imgui();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    shutdown_imgui();
    glfwTerminate();
    return 0;
}

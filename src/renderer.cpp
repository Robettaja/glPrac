#include "renderer.hpp"
#include "vao.hpp"
#include "ebo.hpp"
#include "vbo.hpp"
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

Renderer::Renderer(const glm::vec3& pos) : model(glm::translate(glm::mat4(1.0f), pos))
{
    std::cout << "Renderer created" << std::endl;
}
Renderer::Renderer(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,
                   const std::vector<Texture>& textures, const glm::vec3 pos)
    : vertices(vertices), indices(indices), textures(textures), model(glm::translate(glm::mat4(1.0f), pos))
{
    LinkRenderData();
}
Renderer::~Renderer() = default;

void Renderer::LinkRenderData()
{
    vao.Bind();
    Vbo vbo(vertices);
    Ebo ebo(indices);
    vao.LinkVbo(vbo);
    vao.UnBind();
    ebo.UnBind();
    vbo.UnBind();
}
size_t Renderer::GetVerticesSize() const
{
    return vertices.size();
}
void Renderer::AddVertices(const std::vector<Vertex>& vertexData)
{
    vertices.insert(vertices.end(), vertexData.begin(), vertexData.end());
}
void Renderer::AddIndices(const std::vector<unsigned int>& indicesData)
{
    indices.insert(indices.end(), indicesData.begin(), indicesData.end());
}
void Renderer::SetPosition(const glm::vec3 pos)
{
    model = glm::translate(glm::mat4(1.0f), pos);
}
void Renderer::Draw(const Shader& shader) const
{
    vao.Bind();
    shader.use();
    shader.setMat4("model", model);
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}

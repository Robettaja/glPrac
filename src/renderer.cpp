#include "renderer.hpp"
#include "vao.hpp"
#include "ebo.hpp"
#include "vbo.hpp"
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

Renderer::Renderer(glm::vec3 pos)
{
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
}
Renderer::Renderer(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures,
                   glm::vec3 pos)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    LinkRenderData();
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
}
Renderer::~Renderer()
{
}
void Renderer::LinkRenderData()
{
    vao.Bind();
    Vbo vbo(vertices);
    Ebo ebo(indices);
    vao.LinkVbo(vbo);
    vao.UnBind();
    ebo.UnBind();
    vbo.UnBind();

    for (Texture texture : textures)
    {
        texture.Bind();
    }
}
void Renderer::AddVertices(std::vector<Vertex> vertexData)
{
    vertices.insert(vertices.end(), vertexData.begin(), vertexData.end());
}
void Renderer::AddIndices(std::vector<unsigned int> indicesData)
{
    indices.insert(indices.end(), indicesData.begin(), indicesData.end());
}
void Renderer::Draw(Shader shader)
{
    vao.Bind();
    shader.use();
    shader.setMat4("model", model);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

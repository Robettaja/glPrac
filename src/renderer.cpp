#include "renderer.hpp"
#include "vao.hpp"
#include "ebo.hpp"
#include "vbo.hpp"
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

Renderer::Renderer(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

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

    model = glm::mat4(1.0f);
}
Renderer::~Renderer()
{
}
void Renderer::Draw(Shader& shader, glm::vec3 pos)
{
    vao.Bind();
    shader.use();
    model = glm::translate(model, pos);
    shader.setMat4("model", model);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

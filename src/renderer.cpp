#include "renderer.hpp"
#include "ebo.hpp"
#include "mesh.hpp"
#include "vbo.hpp"
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

Renderer::Renderer(const glm::vec3& pos) : model(glm::translate(glm::mat4(1.0f), pos))
{
}
Renderer::~Renderer()
{
}

void Renderer::SetPosition(const glm::vec3 pos)
{
    model = glm::translate(glm::mat4(1.0f), pos);
}
void Renderer::AddMesh(Mesh& mesh)
{
    this->mesh = &mesh;
}
void Renderer::LinkGL()
{
    vao = std::make_shared<Vao>();
    vao->Bind();
    Vbo vbo(mesh->vertices);
    Ebo ebo(mesh->indices);

    vao->LinkVbo(vbo);
    vao->UnBind();
    ebo.UnBind();
    vbo.UnBind();
}
void Renderer::Draw(const Shader& shader) const
{
    vao->Bind();
    shader.use();
    shader.setMat4("model", model);
    glDrawElements(GL_TRIANGLES, (mesh->GetIndicesAmount()), GL_UNSIGNED_INT, nullptr);
}

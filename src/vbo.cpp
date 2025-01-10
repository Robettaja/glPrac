#include "vbo.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

Vbo::Vbo(const std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);
}
Vbo::~Vbo()
{
    Delete();
}
void Vbo::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void Vbo::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Vbo::Delete() const
{
    glDeleteBuffers(1, &ID);
}

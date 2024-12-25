#include "vbo.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

Vbo::Vbo(std::vector<Vertex> vertices)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}
Vbo::~Vbo()
{
    Delete();
}
void Vbo::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void Vbo::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Vbo::Delete()
{
    glDeleteBuffers(1, &ID);
}

#include "vao.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Vao::Vao()
{
    glGenVertexArrays(1, &ID);
    Bind();
}
Vao::~Vao()
{
    Delete();
}
void Vao::Bind()
{
    glBindVertexArray(ID);
}
void Vao::UnBind()
{
    glBindVertexArray(0);
}
void Vao::LinkVbo(Vbo& vbo)
{
    vbo.Bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    vbo.UnBind();
}
void Vao::Delete()
{
    glDeleteVertexArrays(1, &ID);
}

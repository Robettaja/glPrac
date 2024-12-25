#include "ebo.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

Ebo::Ebo(std::vector<unsigned int> indices)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}
Ebo::~Ebo()
{
    Delete();
}
void Ebo::Bind()
{

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void Ebo::UnBind()
{

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Ebo::Delete()
{
    glDeleteBuffers(1, &ID);
}

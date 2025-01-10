#include "ebo.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

Ebo::Ebo(const std::vector<unsigned int>& indices)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long>(indices.size() * sizeof(unsigned int)), indices.data(), GL_STATIC_DRAW);
}
Ebo::~Ebo()
{
    Delete();
}
void Ebo::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void Ebo::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Ebo::Delete() const
{
    glDeleteBuffers(1, &ID);
}

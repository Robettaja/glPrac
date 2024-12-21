#include "ebo.hpp"

Ebo::Ebo(unsigned int* indices, size_t size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
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

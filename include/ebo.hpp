#pragma once
#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Ebo
{
  public:
    unsigned int ID;
    Ebo(unsigned int* indices, size_t size);
    ~Ebo();
    void Bind();
    void UnBind();
    void Delete();
};

#pragma once
#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Vbo
{
  public:
    unsigned int ID;

    Vbo(float* vertices, size_t size);
    ~Vbo();
    void Bind();
    void UnBind();
    void Delete();
};

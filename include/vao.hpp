#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vbo.hpp"

class Vao
{
  public:
    unsigned int ID;
    Vao();
    ~Vao();
    void Bind();
    void UnBind();
    void Delete();
    void LinkVbo(Vbo& vbo);
};

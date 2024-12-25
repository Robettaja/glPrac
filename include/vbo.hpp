#pragma once

#include "vertex.hpp"
#include <vector>

class Vbo
{
  public:
    unsigned int ID;

    Vbo(std::vector<Vertex> vertices);
    ~Vbo();
    void Bind();
    void UnBind();
    void Delete();
};

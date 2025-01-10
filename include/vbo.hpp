#pragma once

#include "vertex.hpp"

#include <vector>

class Vbo
{
  public:
    unsigned int ID = 0;

    explicit Vbo(const std::vector<Vertex>& vertices);
    ~Vbo();
    void Bind() const;
    void UnBind() const;
    void Delete() const;
};

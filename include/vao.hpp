#pragma once

#include "vbo.hpp"

class Vao
{
  public:
    unsigned int ID = 0;
    Vao();
    ~Vao();
    void Bind() const;
    void UnBind() const;
    void Delete() const;
    void LinkVbo(Vbo& vbo) const;
};

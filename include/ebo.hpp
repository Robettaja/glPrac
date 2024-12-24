#pragma once

#include <cstddef>

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

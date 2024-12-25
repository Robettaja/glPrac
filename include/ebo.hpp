#pragma once

#include <cstddef>
#include <vector>

class Ebo
{
  public:
    unsigned int ID;
    Ebo(std::vector<unsigned int> indices);
    ~Ebo();
    void Bind();
    void UnBind();
    void Delete();
};

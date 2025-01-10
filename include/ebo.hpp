#pragma once

#include <vector>

class Ebo
{
  public:
    unsigned int ID = 0;
    explicit Ebo(const std::vector<unsigned int>& indices);
    ~Ebo();
    void Bind() const;
    void UnBind() const;
    void Delete() const;
};

#pragma once

#include <vector>
class Texture
{
  public:
    unsigned int ID = 0;
    explicit Texture(std::vector<const char*> path);
    void Bind() const;
    void Unbind() const;
};

#pragma once

class Texture
{
  public:
    unsigned int ID = 0;
    explicit Texture(const char* path);
    void Bind() const;
};

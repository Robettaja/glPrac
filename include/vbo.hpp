#pragma once

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

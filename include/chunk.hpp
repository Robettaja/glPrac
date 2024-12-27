#pragma once
#include "renderer.hpp"
#include "block.hpp"

class Chunk
{

  private:
    Block*** blocks;

  public:
    static const int CHUNK_SIZE = 16;

    Chunk();
    ~Chunk();
    void CreateMesh();
    void CreateBlock();
    void Update();
    void Render(Renderer* renderer);
};

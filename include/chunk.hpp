#pragma once
#include "renderer.hpp"
#include "block.hpp"
#include <glm/fwd.hpp>

class Chunk
{

  private:
    Block*** blocks;
    Renderer* renderer;

  public:
    static const int CHUNK_SIZE = 16;

    Chunk();
    ~Chunk();
    void CreateMesh();
    void CreateBlock(int x, int z, int cubeIndex);
    void Update();
    void Render(Shader& shader);
};

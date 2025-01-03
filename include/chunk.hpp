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

    Chunk(glm::vec3 worldPos);
    ~Chunk();
    void SetBlockTypes();
    void CreateMesh();
    void CreateBlock(int x, int y, int z, int cubeIndex);
    void Update();
    void Render(Shader& shader);
};

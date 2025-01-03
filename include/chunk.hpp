#pragma once
#include "renderer.hpp"
#include "block.hpp"
#include <glm/fwd.hpp>

class Chunk
{

  private:
    Block*** blocks;
    Renderer* renderer;
    glm::vec3 chunkPos;
    const int maxHeight = 25;

  public:
    static const int CHUNK_SIZE = 64;

    Chunk(glm::vec3 worldPos);
    ~Chunk();
    void SetBlockTypes();
    void CreateMesh();
    void CreateBlock(int x, int y, int z, int cubeIndex);
    void Update();
    void Render(Shader& shader);
};

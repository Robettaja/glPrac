#pragma once
#include "renderer.hpp"
#include "block.hpp"
#include <glm/fwd.hpp>

enum FaceDirection
{
    Front,
    Down,
    Back,
    Up,
    Right,
    Left,
};

class Chunk
{

  private:
    Block*** blocks;
    Renderer* renderer;
    glm::vec3 chunkPos;
    const int maxHeight = 25;
    int lastVertexSize = 0;

    bool IsFaceVisible(int x, int y, int z, FaceDirection faceDir);

  public:
    static const int CHUNK_SIZE = 2;

    Chunk(glm::vec3 worldPos);
    ~Chunk();
    void SetBlockTypes();
    void CreateMesh();
    void CreateBlock(int x, int y, int z, int cubeIndex);
    void Update();
    void Render(Shader& shader);
};

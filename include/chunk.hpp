#pragma once

#include "renderer.hpp"
#include "block.hpp"
#include <glm/fwd.hpp>

enum class FaceDirection
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
    Mesh* mesh;
    glm::vec3 chunkPos;
    const int maxHeight = 4;
    size_t lastVertexSize = 0;

    bool IsFaceVisible(int x, int y, int z, FaceDirection faceDir) const;

  public:
    static constexpr int CHUNK_SIZE = 16;

    explicit Chunk(glm::vec3 worldPos);
    ~Chunk();
    void SetBlockTypes();
    void CreateMesh();
    void CreateBlock(int x, int y, int z, int cubeIndex);
    void Update();
    bool IsChunkVisible(glm::vec3& cameraPos, glm::vec3& cameraForward) const;
    void Render(const Shader& shader) const;
};

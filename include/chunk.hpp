#pragma once

#include "mesh.hpp"
#include "renderer.hpp"
#include "block.hpp"
#include <glm/fwd.hpp>
#include <memory>

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
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<Mesh> mesh;
    const int maxHeight = 32;
    size_t lastVertexSize = 0;

    bool IsFaceVisible(int x, int y, int z, FaceDirection faceDir) const;

  public:
    glm::vec3 chunkPos;
    bool canLoadGL = false;
    bool isReadyToRender;
    static constexpr int CHUNK_SIZE = 16;

    explicit Chunk(glm::vec3 worldPos);
    ~Chunk();
    void SetBlockTypes();
    void CreateMesh();
    void CreateBlock(int x, int y, int z);
    void LoadGL();
    void Update();
    bool IsChunkVisible(glm::vec3& cameraPos, glm::vec3& cameraForward) const;
    void Render(const Shader& shader) const;
};

#pragma once

#include "chunk.hpp"
#include "camera.hpp"
#include <glm/fwd.hpp>

class ChunkManager
{
  private:
    Shader* shader;
    Camera* camera;
    std::vector<Chunk*> chunks;
    const int CHUNK_AMOUNT_PER_AXIS = 16;

    const bool IsChunkVisible(const glm::vec3& chunkPos);

  public:
    ChunkManager(Shader& shader, Camera& camera);
    ~ChunkManager();
    void Update();
    void Load();
    void Unload();
    static const glm::vec3 WorldToChunkPos(const glm::vec3& worldPos);
};

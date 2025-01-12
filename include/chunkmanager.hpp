#pragma once

#include "chunk.hpp"
#include "camera.hpp"

class ChunkManager
{
  private:
    Shader* shader;
    Camera* camera;
    std::vector<Chunk*> chunks;

    bool IsChunkVisible(const glm::vec3& chunkPos) const;

  public:
    ChunkManager(Shader& shader, Camera& camera);
    void Update();
    void Load();
    void Unload();
};

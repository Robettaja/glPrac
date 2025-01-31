#pragma once

#include "chunk.hpp"
#include "camera.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <mutex>
#include <future>
#include <thread>
#include <unordered_map>
#include <vector>

class ChunkManager
{
  private:
    Shader* shader;
    Camera* camera;
    glm::vec3 lastGenPos;
    std::vector<std::shared_ptr<Chunk>> chunks;
    bool isDataReady = false;
    std::vector<std::thread> threads;
    std::mutex chunksMutex;
    std::future<void> fut;
    const int THREAD_AMOUNT = 8;
    const int CHUNK_AMOUNT_PER_AXIS = 16;

    const bool IsChunkVisible(const glm::vec3& chunkPos);
    void CreateThreads();

  public:
    ChunkManager(Shader& shader, Camera& camera);
    ~ChunkManager();
    void Update();
    void CreateChunks();
    void Load(int threadNum);
    void LoadGL();
    void Unload();
    static const glm::vec3 WorldToChunkPos(const glm::vec3& worldPos);
};

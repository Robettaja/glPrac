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

struct Vec3Hash
{
    std::size_t operator()(const glm::vec3& vec) const noexcept
    {
        std::size_t h1 = std::hash<float>{}(vec.x);
        std::size_t h2 = std::hash<float>{}(vec.y);
        std::size_t h3 = std::hash<float>{}(vec.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class ChunkManager
{
  private:
    Shader* shader;
    Camera* camera;
    glm::vec3 lastGenPos;
    std::unordered_map<glm::vec3, std::shared_ptr<Chunk>, Vec3Hash> chunks;
    bool isDataReady = false;
    std::vector<std::thread> threads;
    std::mutex chunksMutex;
    std::thread fut;
    const int THREAD_AMOUNT = 8;
    const int CHUNK_AMOUNT_PER_AXIS = 16;

    const bool IsChunkVisible(const glm::vec3& chunkPos);
    void CreateThreads();
    int GenerateSeed();

  public:
    static int seed;
    ChunkManager(Shader& shader, Camera& camera);
    ~ChunkManager();
    void Update();
    void CreateChunks();
    void Load(int threadNum);
    void LoadChunk(const glm::vec3& chunkPos);
    void UnloadChunk(const glm::vec3& chunkPos);
    void LoadGL();
    void Unload();
    static glm::vec3 WorldToChunkPos(const glm::vec3& worldPos);
};

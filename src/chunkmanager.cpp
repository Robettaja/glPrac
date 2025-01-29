#include "timer.hpp"
#include "chunkmanager.hpp"
#include "chunk.hpp"
#include <algorithm>
#include <execution>
#include <future>
#include <glm/fwd.hpp>
#include <memory>
#include <thread>
#include <iostream>

Timer timer("Chunk creation timer");

ChunkManager::ChunkManager(Shader& shader, Camera& camera) : shader(&shader), camera(&camera)
{
}
ChunkManager::~ChunkManager()
{
    chunks.clear();
}
void ChunkManager::CreateChunks()
{
    fut = std::async(&ChunkManager::AsyncLoad, this);
}
void ChunkManager::AsyncLoad()
{
    threads.clear();
    for (int i = 0; i < THREAD_AMOUNT; i++)
    {
        threads.emplace_back(&ChunkManager::Load, this, i);
    }
    for (auto& thread : threads)
    {
        thread.join();
    }
}
void ChunkManager::Load(int threadNum)
{
    chunksReadyCount = 0;
    std::lock_guard<std::mutex> lock(chunksMutex);
    for (size_t i = threadNum * THREAD_AMOUNT; i < CHUNK_AMOUNT_PER_AXIS / THREAD_AMOUNT * (threadNum + 1); i++)
    {
        for (size_t j = 0; j < CHUNK_AMOUNT_PER_AXIS; j++)
        {
            glm::vec3 startPos = glm::vec3(camera->position.x - CHUNK_AMOUNT_PER_AXIS * Chunk::CHUNK_SIZE / 2, //
                                           0,                                                                  //
                                           camera->position.z - CHUNK_AMOUNT_PER_AXIS * Chunk::CHUNK_SIZE / 2);
            glm::vec3 posOff = WorldToChunkPos(startPos);
            glm::vec3 pos = glm::vec3(posOff.x + i * Chunk::CHUNK_SIZE, 0, posOff.z + j * Chunk::CHUNK_SIZE);
            lastGenPos = pos;
            std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(pos);
            chunks.emplace_back(chunk);
            chunksReadyCount++;
        }
    }
    std::cout << "Thread " << threadNum << " finished" << std::endl;
}
void ChunkManager::LoadGL()
{
    for (auto& chunk : chunks)
    {
        chunk->LoadGL();
    }
}
void ChunkManager::Unload()
{
    chunks.clear();
}
const glm::vec3 ChunkManager::WorldToChunkPos(const glm::vec3& worldPos)
{
    return glm::vec3(std::floor(worldPos.x / Chunk::CHUNK_SIZE) * Chunk::CHUNK_SIZE,
                     std::floor(worldPos.y / Chunk::CHUNK_SIZE) * Chunk::CHUNK_SIZE,
                     std::floor(worldPos.z / Chunk::CHUNK_SIZE) * Chunk::CHUNK_SIZE);
}
void ChunkManager::Update()
{
    if (fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready && !isDataReady)
    {
        isDataReady = true;
        LoadGL();
    }
    // if (glm::distance(camera->position, lastGenPos) > 200)
    // {
    //     AsyncLoad();
    // }
    if (isDataReady)
    {
        for (auto& chunk : chunks)
        {
            if (chunk->IsChunkVisible(camera->position, camera->orientation))
            {
                chunk->Render(*shader);
            }
        }
    }
}

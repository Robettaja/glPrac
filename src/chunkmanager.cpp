#include "timer.hpp"
#include "chunkmanager.hpp"
#include "chunk.hpp"
#include <cstddef>
#include <future>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <memory>
#include <thread>
#include <random>
#include <iostream>

Timer timer("Chunk creation timer");

int ChunkManager::seed;
ChunkManager::ChunkManager(Shader& shader, Camera& camera) : shader(&shader), camera(&camera)
{
    seed = GenerateSeed();
    std::cout << "Seed: " << seed << std::endl;
}
ChunkManager::~ChunkManager()
{
    chunks.clear();
}
int ChunkManager::GenerateSeed()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    std::uniform_int_distribution<int> distribution(100000000, 999999999);

    unsigned int randomNumber = distribution(generator);
    return randomNumber;
}
void ChunkManager::CreateChunks()
{
    fut = std::async(&ChunkManager::CreateThreads, this);
}
void ChunkManager::CreateThreads()
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
    size_t chunksPerThread = CHUNK_AMOUNT_PER_AXIS / THREAD_AMOUNT;
    size_t startChunk = threadNum * chunksPerThread;
    size_t endChunk = startChunk + chunksPerThread;
    std::lock_guard<std::mutex> lock(chunksMutex);
    for (size_t i = startChunk; i < endChunk; i++)
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
            chunk->canLoadGL = true;
            chunks.emplace_back(chunk);
        }
    }
}
void ChunkManager::LoadChunk(const glm::vec3& chunkPos)
{
    std::lock_guard<std::mutex> lock(chunksMutex);
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(chunkPos);
    chunk->canLoadGL = true;
    chunks.emplace_back(chunk);
}
void ChunkManager::LoadGL()
{
    for (auto& chunk : chunks)
    {
        if (chunk->canLoadGL)
        {
            chunk->LoadGL();
            chunk->canLoadGL = false;
        }
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
    if (glm::distance(camera->position, lastGenPos) > 50)
    {
    }
    LoadGL();
    for (auto& chunk : chunks)
    {
        if (chunk->isReadyToRender)
            if (chunk->IsChunkVisible(camera->position, camera->orientation))
            {
                chunk->Render(*shader);
            }
    }
}

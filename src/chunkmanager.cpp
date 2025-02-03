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
#include <ranges>

Timer timer("Chunk creation timer");

int ChunkManager::seed;
ChunkManager::ChunkManager(Shader& shader, Camera& camera) : shader(&shader), camera(&camera)
{
    seed = GenerateSeed();
    std::cout << "Seed: " << seed << std::endl;
}
ChunkManager::~ChunkManager()
{
    fut.join();
    chunks.clear();
}
bool ChunkManager::HasCurrentChunkChanged()
{
    return WorldToChunkPos(camera->position) != WorldToChunkPos(lastChunkPos);
}
int ChunkManager::GenerateSeed()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    std::uniform_int_distribution<int> distribution(100000000, 999999999);

    unsigned int randomNumber = distribution(generator);
    return randomNumber;
}
BoundingBox ChunkManager::GetChunkBoundingBox()
{
    int minX = INT_MAX;
    int minY = INT_MAX;
    int minZ = INT_MAX;
    int maxX = INT_MIN;
    int maxY = INT_MIN;
    int maxZ = INT_MIN;
    for (auto& chunkPos : currentChunksPos)
    {
        if (minX > chunkPos.x)
            minX = chunkPos.x;
        if (minY > chunkPos.y)
            minY = chunkPos.y;
        if (minZ > chunkPos.z)
            minZ = chunkPos.z;
        if (maxX < chunkPos.x)
            maxX = chunkPos.x;
        if (maxY < chunkPos.y)
            maxY = chunkPos.y;
        if (maxZ < chunkPos.z)
            maxZ = chunkPos.z;
    }
    return BoundingBox{glm::vec3(minX, minY, minZ), glm::vec3(maxX, maxY, maxZ)};
}
void ChunkManager::RemoveChunkPositions()
{
    std::vector<int> indexes;
    for (int i = 0; i < currentChunksPos.size(); i++)
    {
        // Add indexes to remove if key is not in the map.
        if (chunks.find(currentChunksPos[i]) == chunks.end())
        {
            indexes.emplace_back(i);
        }
    }
    for (int i = indexes.size() - 1; i > 0; i--)
    {
        currentChunksPos.erase(currentChunksPos.begin() + indexes[i]);
    }
}
void ChunkManager::CreateChunks()
{
    fut = std::thread(&ChunkManager::CreateThreads, this);
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
            std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(pos);
            chunk->canLoadGL = true;
            currentChunksPos.emplace_back(pos);
            chunks[pos] = chunk;
        }
    }
}
void ChunkManager::LoadChunk(const glm::vec3& chunkPos)
{
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(chunkPos);
    chunk->canLoadGL = true;
    chunks[chunkPos] = chunk;
}
void ChunkManager::UnloadChunk(const glm::vec3& chunkPos)
{
    chunks.erase(chunkPos);
}
void ChunkManager::LoadGL()
{
    for (auto& chunk : std::views::values(chunks))
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
glm::vec3 ChunkManager::WorldToChunkPos(const glm::vec3& worldPos)
{
    return glm::vec3(std::floor(worldPos.x / Chunk::CHUNK_SIZE) * Chunk::CHUNK_SIZE,
                     std::floor(worldPos.y / Chunk::CHUNK_SIZE) * Chunk::CHUNK_SIZE,
                     std::floor(worldPos.z / Chunk::CHUNK_SIZE) * Chunk::CHUNK_SIZE);
}
void ChunkManager::Update()
{

    LoadGL();
    for (auto& chunk : std::views::values(chunks))
    {
        if (chunk->isReadyToRender)
        {
            if (chunk->IsChunkVisible(camera->position, camera->orientation))
            {
                chunk->Render(*shader);
            }
        }
    }
    if (HasCurrentChunkChanged())
    {
        // Chunk unloading
        for (auto& chunkPos : currentChunksPos)
        {
            if (glm::distance(camera->position, chunkPos) > CHUNK_AMOUNT_PER_AXIS * Chunk::CHUNK_SIZE)
            {
                UnloadChunk(chunkPos);
            }
        }
        RemoveChunkPositions();
        // Chunk loading
    }
    lastChunkPos = camera->position;
}

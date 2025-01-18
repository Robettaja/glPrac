#include "chunkmanager.hpp"
#include "chunk.hpp"
#include <future>
#include <glm/fwd.hpp>

ChunkManager::ChunkManager(Shader& shader, Camera& camera) : shader(&shader), camera(&camera)
{
}
ChunkManager::~ChunkManager()
{
    for (auto& chunk : chunks)
    {
        delete chunk;
    }
    chunks.clear();
}
void ChunkManager::AsyncLoad()
{
    isDataReady = false;
    fut = std::async(std::launch::async, &ChunkManager::Load, this);
}
void ChunkManager::Load()
{
    std::lock_guard<std::mutex> lock(chunksMutex);
    for (size_t i = 0; i < CHUNK_AMOUNT_PER_AXIS; i++)
    {
        for (size_t j = 0; j < CHUNK_AMOUNT_PER_AXIS; j++)
        {
            glm::vec3 startPos = glm::vec3(camera->position.x - CHUNK_AMOUNT_PER_AXIS * Chunk::CHUNK_SIZE / 2, //
                                           0,                                                                  //
                                           camera->position.z - CHUNK_AMOUNT_PER_AXIS * Chunk::CHUNK_SIZE / 2);
            glm::vec3 posOff = WorldToChunkPos(startPos);
            glm::vec3 pos = glm::vec3(posOff.x + i * Chunk::CHUNK_SIZE, 0, posOff.z + j * Chunk::CHUNK_SIZE);
            Chunk* chunk = new Chunk(pos);
            chunks.emplace_back(chunk);
        }
    }
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
    for (auto& chunk : chunks)
    {
        delete chunk;
    }
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
        LoadGL();
        isDataReady = true;
    }
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

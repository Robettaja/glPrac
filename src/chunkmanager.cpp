#include "chunkmanager.hpp"
#include "chunk.hpp"
#include <glm/fwd.hpp>

ChunkManager::ChunkManager(Shader& shader, Camera& camera) : shader(&shader), camera(&camera)
{
}
void ChunkManager::Load()
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            glm::vec3 pos = glm::vec3(i * Chunk::CHUNK_SIZE, 0, j * Chunk::CHUNK_SIZE);
            chunks.emplace_back(new Chunk(pos));
        }
    }
}
void ChunkManager::Update()
{
    for (auto& chunk : chunks)
    {
        chunk->Render(*shader);
    }
}

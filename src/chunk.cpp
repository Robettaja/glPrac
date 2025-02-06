#include "chunk.hpp"
#include "block.hpp"
#include "chunkmanager.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include <cstdlib>
#include <glm/common.hpp>
#include <glm/exponential.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/noise.hpp>
#include <vendor/FastNoiseLite.h>
#include <vector>
#include <cmath>
#include <iostream>
Chunk::Chunk(const glm::vec3 worldPos) : chunkPos(worldPos)
{
    renderer = std::make_shared<Renderer>(worldPos);
    blocks = new Block**[CHUNK_SIZE];
    for (size_t x = 0; x < CHUNK_SIZE; x++)
    {
        blocks[x] = new Block*[CHUNK_SIZE];
        for (size_t y = 0; y < CHUNK_SIZE; y++)
        {
            blocks[x][y] = new Block[CHUNK_SIZE];
        }
    }
    SetBlockTypes();
    CreateMesh();
}
Chunk::~Chunk()
{
    for (size_t x = 0; x < CHUNK_SIZE; x++)
    {
        for (size_t y = 0; y < CHUNK_SIZE; y++)
        {
            delete[] blocks[x][y];
        }
        delete[] blocks[x];
    }
    delete[] blocks;
}
void Chunk::SetBlockTypes()
{
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                float xPos = (chunkPos.x + x) / 1;
                float yPos = (chunkPos.z + z) / 1;
                FastNoiseLite noise;
                noise.SetSeed(ChunkManager::seed);
                noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
                noise.SetFractalOctaves(4);
                float noiseValue = glm::abs(noise.GetNoise(xPos, yPos));
                int heightMap = noiseValue * maxHeight;

                if (y <= heightMap)
                {
                    blocks[x][y][z].SetBlockType(BlockType::Grass);
                }
                else
                {
                    blocks[x][y][z].SetBlockType(BlockType::Air);
                }
            }
        }
    }
}
void Chunk::CreateMesh()
{
    mesh = std::make_shared<Mesh>();
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if (!blocks[x][y][z].IsActive())
                    continue;

                CreateBlock(x, y, z);
            }
        }
    }
    renderer->AddMesh(*mesh);
    lastVertexSize = 0;
}
void Chunk::CreateBlock(const int x, const int y, const int z)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    const size_t verticeCount = mesh->GetVertexAmount();
    if (IsFaceVisible(x, y, z, FaceDirection::Front))
    {
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(0, 0), (glm::vec3(0, 0, 1))});
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(1, 0), (glm::vec3(0, 0, 1))});
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1), (glm::vec3(0, 0, 1))});
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(0, 1), (glm::vec3(0, 0, 1))});
    }

    if (0 && IsFaceVisible(x, y, z, FaceDirection::Down))
    {
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(1, 1), (glm::vec3(0, -1, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(0, 1), (glm::vec3(0, -1, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0), (glm::vec3(0, -1, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(1, 0), (glm::vec3(0, -1, 0))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Back))
    {
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(1, 0), (glm::vec3(0, 0, -1))});
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0), (glm::vec3(0, 0, -1))});
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1), (glm::vec3(0, 0, -1))});
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(1, 1), (glm::vec3(0, 0, -1))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Up))
    {
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(0, 1), (glm::vec3(0, 1, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1), (glm::vec3(0, 1, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(1, 0), (glm::vec3(0, 1, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(0, 0), (glm::vec3(0, 1, 0))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Left))
    {
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0), (glm::vec3(-1, 0, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(1, 0), (glm::vec3(-1, 0, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1), (glm::vec3(-1, 0, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1), (glm::vec3(-1, 0, 0))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Right))
    {
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(1, 0), (glm::vec3(1, 0, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0), (glm::vec3(1, 0, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1), (glm::vec3(1, 0, 0))});
        vertices.emplace_back(Vertex{glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1), (glm::vec3(1, 0, 0))});
    }
    lastVertexSize = vertices.size();

    for (size_t i = 0; i < vertices.size(); i += 4)
    {
        indices.emplace_back(0 + verticeCount + i);
        indices.emplace_back(1 + verticeCount + i);
        indices.emplace_back(2 + verticeCount + i);
        indices.emplace_back(2 + verticeCount + i);
        indices.emplace_back(3 + verticeCount + i);
        indices.emplace_back(0 + verticeCount + i);
    }
    mesh->AddVertices(vertices);
    mesh->AddIndices(indices);
}
void Chunk::LoadGL()
{
    renderer->LinkGL();
    isReadyToRender = true;
}
void Chunk::Update()
{
}
bool Chunk::IsChunkVisible(glm::vec3& cameraPos, glm::vec3& cameraForward) const
{
    glm::vec3 centerChunkPos = chunkPos;
    centerChunkPos.x += CHUNK_SIZE / 2;
    centerChunkPos.z += CHUNK_SIZE / 2;
    float distanceToChunk = glm::distance(cameraPos, centerChunkPos);
    if (distanceToChunk < Chunk::CHUNK_SIZE * 1.1)
        return true;
    if (distanceToChunk > 100)
        return false;

    float visionThreshold = glm::dot(glm::normalize(centerChunkPos - cameraPos), cameraForward);
    return visionThreshold >= 0.25f;
}
bool Chunk::IsFaceVisible(const int x, const int y, const int z, const FaceDirection faceDir) const
{
    int nX = x, nY = y, nZ = z;

    switch (faceDir)
    {
    case FaceDirection::Front:
        if (nZ >= CHUNK_SIZE - 1)
            return true;
        nZ++;
        break;
    case FaceDirection::Down:
        if (nY <= 0)
            return true;
        nY--;
        break;
    case FaceDirection::Back:
        if (nZ <= 0)
            return true;
        nZ--;
        break;
    case FaceDirection::Up:
        if (nY >= CHUNK_SIZE - 1)
            return true;
        nY++;
        break;
    case FaceDirection::Right:
        if (nX >= CHUNK_SIZE - 1)
            return true;
        nX++;
        break;
    case FaceDirection::Left:
        if (nX <= 0)
            return true;
        nX--;
        break;
    }

    return !blocks[nX][nY][nZ].IsActive();
}
void Chunk::Render(const Shader& shader) const
{
    renderer->Draw(shader);
}

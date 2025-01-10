#include "logger.hpp"
#include "chunk.hpp"
#include "block.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include <cstdlib>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/noise.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

Chunk::Chunk(const glm::vec3 worldPos) : chunkPos(worldPos)
{
    renderer = new Renderer(worldPos);
    blocks = new Block**[CHUNK_SIZE];
    for (size_t i = 0; i < CHUNK_SIZE; i++)
    {
        blocks[i] = new Block*[CHUNK_SIZE];
        for (size_t j = 0; j < CHUNK_SIZE; j++)
        {
            blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
    SetBlockTypes();
}
Chunk::~Chunk()
{
    for (size_t i = 0; i < CHUNK_SIZE; i++)
    {
        for (size_t j = 0; j < CHUNK_SIZE; j++)
        {
            delete[] blocks[i][j];
        }
        delete[] blocks[i];
    }
    delete[] blocks;
    delete renderer;
}
void Chunk::SetBlockTypes()
{
    int counter = 0;
    for (size_t x = 0; x < CHUNK_SIZE; x++)
    {
        for (size_t y = 0; y < CHUNK_SIZE; y++)
        {
            for (size_t z = 0; z < CHUNK_SIZE; z++)
            {
                // float noiseValue =
                //     std::abs(glm::perlin(glm::vec2(chunkPos.x - x, chunkPos.z - z) * (float)(1.0f / CHUNK_SIZE)));
                // int heightMap = noiseValue * maxHeight;
                int heightMap = 0;
                if (y == 0)
                {
                    counter++;
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
    int counter = 0;
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if (!blocks[x][y][z].IsActive())
                    continue;

                CreateBlock(x, y, z, counter);
                counter++;
            }
        }
    }
    renderer->LinkRenderData();
    lastVertexSize = 0;
}
void Chunk::CreateBlock(const int x, const int y, const int z, const int cubeIndex)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    const unsigned int cubeNum = lastVertexSize * cubeIndex;
    if (IsFaceVisible(x, y, z, FaceDirection::Front))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, 1))});
    }

    if (IsFaceVisible(x, y, z, FaceDirection::Down))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, -1, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, -1, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, -1, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, -1, 0))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Back))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, -1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, -1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, -1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, -1))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Up))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, 1))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Left))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(-1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(-1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(-1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(-1, 0, 0))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Right))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(1, 0, 0))});
    }
    lastVertexSize = vertices.size();

    for (size_t i = 0; i < vertices.size(); i += 4)
    {
        indices.emplace_back(0 + cubeNum + i);
        indices.emplace_back(1 + cubeNum + i);
        indices.emplace_back(2 + cubeNum + i);
        indices.emplace_back(2 + cubeNum + i);
        indices.emplace_back(3 + cubeNum + i);
        indices.emplace_back(0 + cubeNum + i);
    }
    logger::log_info(std::to_string(vertices.size()));
    // std::cout << vertices.size() << " " << indices.size() << std::endl;
    // std::cout << x << " " << y << " " << z << " " << blocks[x][y][z].GetBlockData() << std::endl;
    renderer->AddVertices(vertices);
    renderer->AddIndices(indices);
}
void Chunk::Update()
{
}
bool Chunk::IsFaceVisible(const int x, const int y, const int z, const FaceDirection faceDir) const
{
    // return true;
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

    // if (faceDir == FaceDirection::Up)
    //     std::cout << x << " " << y << " " << z << " " << !blocks[nX][nY][nZ].IsSolid() << std::endl;
    return !blocks[nX][nY][nZ].IsActive();
}
void Chunk::Render(const Shader& shader) const
{
    renderer->Draw(shader);
}

#include "chunk.hpp"
#include "block.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include <cstdlib>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/noise.hpp>
#include <vector>
#include <cmath>

Chunk::Chunk(glm::vec3 worldPos)
{
    renderer = new Renderer(worldPos);
    chunkPos = worldPos;
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
                if (y == 1)
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
    int counter = 0;
    for (size_t x = 0; x < CHUNK_SIZE; x++)
    {
        for (size_t y = 0; y < CHUNK_SIZE; y++)
        {
            for (size_t z = 0; z < CHUNK_SIZE; z++)
            {
                if (blocks[x][y][z].IsActive() == false)
                    continue;

                CreateBlock(x, y, z, counter);
                counter++;
            }
        }
    }
    renderer->LinkRenderData();
    lastVertexSize = 0;
}
void Chunk::CreateBlock(int x, int y, int z, int cubeIndex)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int cubeNum = lastVertexSize * cubeIndex;
    if (IsFaceVisible(x, y, z, FaceDirection::Front))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y - 0.5f, z + 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y - 0.5f, z + 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y + 0.5f, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y + 0.5f, z + 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, 1))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Down))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y - 0.5f, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, -1, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y - 0.5f, z + 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, -1, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y - 0.5f, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, -1, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y - 0.5f, z - 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, -1, 0))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Back))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y - 0.5f, z - 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, -1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y - 0.5f, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, -1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y + 0.5f, z - 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, -1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y + 0.5f, z - 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, -1))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Up))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y + 0.5f, z + 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y + 0.5f, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y + 0.5f, z - 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, 1))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y + 0.5f, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, 1))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Left))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y - 0.5f, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(-1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y - 0.5f, z + 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(-1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y + 0.5f, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(-1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x - 0.5f, y + 0.5f, z - 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(-1, 0, 0))});
    }
    if (IsFaceVisible(x, y, z, FaceDirection::Right))
    {
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y - 0.5f, z + 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y - 0.5f, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y + 0.5f, z - 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(1, 0, 0))});
        vertices.emplace_back(
            Vertex{glm::vec3(x + 0.5f, y + 0.5f, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(1, 0, 0))});
    }
    lastVertexSize = vertices.size();

    for (size_t i = 0; i < vertices.size() / 4; i++)
    {
        int n = i * 4;
        indices.emplace_back(0 + cubeNum + n);
        indices.emplace_back(1 + cubeNum + n);
        indices.emplace_back(2 + cubeNum + n);
        indices.emplace_back(2 + cubeNum + n);
        indices.emplace_back(3 + cubeNum + n);
        indices.emplace_back(0 + cubeNum + n);
    }
    renderer->AddVertices(vertices);
    renderer->AddIndices(indices);
}
bool Chunk::IsFaceVisible(int x, int y, int z, FaceDirection faceDir)
{
    if (x == 0 || x == CHUNK_SIZE - 1 || z == 0 || z == CHUNK_SIZE - 1)
        return true;

    switch (faceDir)
    {
    case FaceDirection::Front:
        z++;
        break;
    case FaceDirection::Down:
        y--;
        break;
    case FaceDirection::Back:
        z--;
        break;
    case FaceDirection::Up:
        y++;
        break;
    case FaceDirection::Right:
        x++;
        break;
    case FaceDirection::Left:
        x--;
        break;
    }

    return !blocks[x][y][z].IsSolid();
}
void Chunk::Render(Shader& shader)
{
    renderer->Draw(shader);
}

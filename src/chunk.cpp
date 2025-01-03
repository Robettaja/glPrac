#include "chunk.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include <cstdlib>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/noise.hpp>
#include <vector>
#include <cmath>
#include <iostream>

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
                float noiseValue =
                    std::abs(glm::perlin(glm::vec2(chunkPos.x - x, chunkPos.z - z) * (float)(1.0f / CHUNK_SIZE)));
                int heightMap = noiseValue * maxHeight;
                if (y == CHUNK_SIZE / 2 - heightMap)
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
    int chunkStart = std::ceil(CHUNK_SIZE / 2);
    for (size_t x = 0; x < CHUNK_SIZE; x++)
    {
        for (size_t y = 0; y < CHUNK_SIZE; y++)
        {
            for (size_t z = 0; z < CHUNK_SIZE; z++)
            {
                if (blocks[x][y][z].IsActive() == false)
                    continue;

                CreateBlock(chunkStart - x, chunkStart - y, chunkStart - z, counter);
                counter++;
            }
        }
    }
    renderer->LinkRenderData();
}
void Chunk::CreateBlock(int x, int y, int z, int cubeIndex)
{
    std::vector<Vertex> vertices{
        // Main side
        Vertex{glm::vec3(x - 0.5f, y - 0.5f, z + 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(x + 0.5f, y - 0.5f, z + 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(x + 0.5f, y + 0.5f, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(x - 0.5f, y + 0.5f, z + 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, 1))},
        // Bottom side
        Vertex{glm::vec3(x + 0.5f, y - 0.5f, z + 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, -1, 0))},
        Vertex{glm::vec3(x - 0.5f, y - 0.5f, z + 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, -1, 0))},
        Vertex{glm::vec3(x - 0.5f, y - 0.5f, z - 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, -1, 0))},
        Vertex{glm::vec3(x + 0.5f, y - 0.5f, z - 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, -1, 0))},
        // Back Side
        Vertex{glm::vec3(x + 0.5f, y - 0.5f, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, -1))},
        Vertex{glm::vec3(x - 0.5f, y - 0.5f, z - 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, -1))},
        Vertex{glm::vec3(x - 0.5f, y + 0.5f, z - 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, -1))},
        Vertex{glm::vec3(x + 0.5f, y + 0.5f, z - 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, -1))},
        // Top Side
        Vertex{glm::vec3(x - 0.5f, y + 0.5f, z + 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(x + 0.5f, y + 0.5f, z + 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(x + 0.5f, y + 0.5f, z - 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(x - 0.5f, y + 0.5f, z - 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, 1))},
        // Left Side
        Vertex{glm::vec3(x - 0.5f, y - 0.5f, z - 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(-1, 0, 0))},
        Vertex{glm::vec3(x - 0.5f, y - 0.5f, z + 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(-1, 0, 0))},
        Vertex{glm::vec3(x - 0.5f, y + 0.5f, z + 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(-1, 0, 0))},
        Vertex{glm::vec3(x - 0.5f, y + 0.5f, z - 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(-1, 0, 0))},
        // Right Side
        Vertex{glm::vec3(x + 0.5f, y - 0.5f, z + 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(1, 0, 0))},
        Vertex{glm::vec3(x + 0.5f, y - 0.5f, z - 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(1, 0, 0))},
        Vertex{glm::vec3(x + 0.5f, y + 0.5f, z - 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(1, 0, 0))},
        Vertex{glm::vec3(x + 0.5f, y + 0.5f, z + 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(1, 0, 0))},

    };
    unsigned int cubeNum = 24 * cubeIndex;
    std::vector<unsigned int> indices{
        // Main side
        0 + cubeNum, 1 + cubeNum, 2 + cubeNum, //
        2 + cubeNum, 3 + cubeNum, 0 + cubeNum, //
        // Bottom side
        4 + cubeNum, 5 + cubeNum, 6 + cubeNum, //
        6 + cubeNum, 7 + cubeNum, 4 + cubeNum, //
        // Back Side
        8 + cubeNum, 9 + cubeNum, 10 + cubeNum,  //
        10 + cubeNum, 11 + cubeNum, 8 + cubeNum, //
        // Top Side
        12 + cubeNum, 13 + cubeNum, 14 + cubeNum, //
        14 + cubeNum, 15 + cubeNum, 12 + cubeNum, //
        // Left Side
        16 + cubeNum, 17 + cubeNum, 18 + cubeNum, //
        18 + cubeNum, 19 + cubeNum, 16 + cubeNum, //
        // Right Side
        20 + cubeNum, 21 + cubeNum, 22 + cubeNum, //
        22 + cubeNum, 23 + cubeNum, 20 + cubeNum, //
    };
    renderer->AddVertices(vertices);
    renderer->AddIndices(indices);
}
void Chunk::Render(Shader& shader)
{
    renderer->Draw(shader);
}

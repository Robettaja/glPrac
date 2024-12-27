#include "chunk.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <vector>

Chunk::Chunk()
{
    blocks = new Block**[CHUNK_SIZE];
    for (size_t i = 0; i < CHUNK_SIZE; i++)
    {
        blocks[i] = new Block*[CHUNK_SIZE];
        for (size_t j = 0; j < CHUNK_SIZE; j++)
        {
            blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
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
}
void Chunk::CreateMesh()
{
    for (size_t x = 0; x < CHUNK_SIZE; x++)
    {
        for (size_t y = 0; y < CHUNK_SIZE; y++)
        {
            for (size_t z = 0; z < CHUNK_SIZE; z++)
            {
                if (blocks[x][y][z].IsActive() == false)
                    continue;
            }
            CreateBlock();
        }
    }
}
void Chunk::CreateBlock()
{
    std::vector<Vertex> vertices{
        // Main side
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(0.5f, -0.5f, 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(0.5f, 0.5f, 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, 1))},
        // Bottom side
        Vertex{glm::vec3(0.5f, -0.5f, 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, -1, 0))},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, -1, 0))},
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, -1, 0))},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, -1, 0))},
        // Back Side
        Vertex{glm::vec3(0.5f, -0.5f, -0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, -1))},
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, -1))},
        Vertex{glm::vec3(0.5f, 0.5f, -0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, -1))},
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, -1))},
        // Top Side
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(0.5f, 0.5f, 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(0.5f, 0.5f, -0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(0, 0, 1))},
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(0, 0, 1))},
        // Left Side
        Vertex{glm::vec3(-0.5f, -0.5f, -0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(-1, 0, 0))},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(-1, 0, 0))},
        Vertex{glm::vec3(-0.5f, 0.5f, 0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(-1, 0, 0))},
        Vertex{glm::vec3(-0.5f, 0.5f, -0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(-1, 0, 0))},
        // Right Side
        Vertex{glm::vec3(0.5f, -0.5f, 0.5), glm::vec2(0, 0), glm::normalize(glm::vec3(1, 0, 0))},
        Vertex{glm::vec3(0.5f, -0.5f, -0.5), glm::vec2(1, 0), glm::normalize(glm::vec3(1, 0, 0))},
        Vertex{glm::vec3(0.5f, 0.5f, -0.5), glm::vec2(1, 1), glm::normalize(glm::vec3(1, 0, 0))},
        Vertex{glm::vec3(0.5f, 0.5f, 0.5), glm::vec2(0, 1), glm::normalize(glm::vec3(1, 0, 0))},

    };
    std::vector<unsigned int> indices{
        // Main side
        0, 1, 2, //
        2, 3, 0, //
        // Bottom side
        4, 5, 6, //
        6, 7, 4, //
        // Back Side
        8, 9, 10,  //
        10, 11, 8, //
        // Top Side
        12, 13, 14, //
        14, 15, 12, //
        // Left Side
        16, 17, 18, //
        18, 19, 16, //
        // Right Side
        20, 21, 22, //
        22, 23, 20, //

    };
    Texture texture("textures/stone.jpg");
    std::vector<Texture> textures;
    textures.emplace_back(texture);
    Renderer renderer(vertices, indices, textures, glm::vec3(2, 3, 7));
    Shader shader("shaders/vertex.vert", "shaders/fragment.frag");
    renderer.Draw(shader);
}

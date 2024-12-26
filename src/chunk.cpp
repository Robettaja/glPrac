#include "chunk.hpp"
#include "vertex.hpp"

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
        }
    }
}
void Chunk::CreateBlock()
{
}

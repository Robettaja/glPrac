#include "block.hpp"
#include <vector>
#include <iostream>

Block::Block()
{
    model = glm::mat4(1);
    vertexData = AsingVertexData();
    indices = new unsigned int;
}
Block::~Block()
{
    delete[] vertexData;
    delete indices;
}
float* Block::AsingVertexData()
{
    std::vector<glm::vec3> positions;
    positions.emplace_back(glm::vec3(-1, -1, -1));
    positions.emplace_back(glm::vec3(1, -1, -1));
    positions.emplace_back(glm::vec3(1, 1, -1));
    positions.emplace_back(glm::vec3(-1, 1, -1));
    positions.emplace_back(glm::vec3(-1, -1, -1));
    positions.emplace_back(glm::vec3(1, -1, 1));
    positions.emplace_back(glm::vec3(1, 1, 1));
    positions.emplace_back(glm::vec3(-1, 1, 1));

    std::vector<glm::vec2> uvs;
    uvs.emplace_back(glm::vec2(0, 0));
    uvs.emplace_back(glm::vec2(1, 0));
    uvs.emplace_back(glm::vec2(1, 1));
    uvs.emplace_back(glm::vec2(0, 1));
    uvs.emplace_back(glm::vec2(0, 0));
    uvs.emplace_back(glm::vec2(1, 0));
    uvs.emplace_back(glm::vec2(1, 0));
    uvs.emplace_back(glm::vec2(0, 1));

    std::vector<glm::vec3> normals;
    normals.emplace_back(glm::vec3(-1, -1, -1));
    normals.emplace_back(glm::vec3(1, -1, -1));
    normals.emplace_back(glm::vec3(1, 1, -1));
    normals.emplace_back(glm::vec3(-1, 1, -1));
    normals.emplace_back(glm::vec3(-1, -1, 1));
    normals.emplace_back(glm::vec3(1, -1, 1));
    normals.emplace_back(glm::vec3(-1, -1, -1));
    normals.emplace_back(glm::vec3(-1, 1, 1));

    float* data = new float[3 * positions.size() + 2 * uvs.size() + 3 * normals.size()];

    int offset = 0;
    for (int i = 0; i < 8; i++)
    {
        data[offset] = positions[i].x;
        data[offset + 1] = positions[i].y;
        data[offset + 2] = positions[i].z;

        data[offset + 3] = uvs[i].x;
        data[offset + 4] = uvs[i].y;

        data[offset + 5] = normals[i].x;
        data[offset + 6] = normals[i].y;
        data[offset + 7] = normals[i].z;
        offset += 8;
    }

    return data;
}
unsigned int* Block::AsingIndices()
{
    unsigned int* testi = new unsigned int;
    return testi;
}
void Block::SetupResources()
{
}
void Block::Draw()
{
    std::cout << "piirtää :)" << std::endl;
}

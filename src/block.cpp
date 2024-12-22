
#include "block.hpp"
#include "vbo.hpp"
#include "vao.hpp"
#include "ebo.hpp"
#include "texture.hpp"

#include <glm/fwd.hpp>
#include <vector>

Block::Block()
{
    model = glm::mat4(1);
    vertexData = AssignVertexData();
    indices = AssignIndices();

    SetupResources();
}
Block::~Block()
{
    delete[] vertexData;
    delete[] indices;
}
float* Block::AssignVertexData()
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
unsigned int* Block::AssignIndices()
{
    std::vector<glm::vec3> indices;
    indices.emplace_back(glm::vec3(4, 5, 6));
    indices.emplace_back(glm::vec3(6, 7, 4));
    indices.emplace_back(glm::vec3(0, 6, 2));
    indices.emplace_back(glm::vec3(2, 1, 0));
    indices.emplace_back(glm::vec3(0, 4, 7));
    indices.emplace_back(glm::vec3(7, 3, 0));
    indices.emplace_back(glm::vec3(1, 2, 6));
    indices.emplace_back(glm::vec3(6, 5, 1));
    indices.emplace_back(glm::vec3(3, 7, 6));
    indices.emplace_back(glm::vec3(6, 2, 3));
    indices.emplace_back(glm::vec3(0, 1, 5));
    indices.emplace_back(glm::vec3(5, 4, 0));

    unsigned int* data = new unsigned int[3 * indices.size()];
    int offset = 0;
    for (int i = 0; i < indices.size(); i++)
    {
        data[offset] = indices[i].x;
        data[offset + 1] = indices[i].y;
        data[offset + 2] = indices[i].z;
        offset += 3;
    }
    return data;
}

void Block::SetupResources()
{
}
void Block::Draw()
{
}

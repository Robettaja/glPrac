#include <glad/glad.h>

#include "block.hpp"
#include "shader.hpp"
#include "vbo.hpp"
#include "vao.hpp"
#include "ebo.hpp"
#include "texture.hpp"
#include <iostream>

#include <glm/fwd.hpp>
#include <memory>
#include <vector>

Block::Block(glm::vec3 position)
{
    model = glm::mat4(1);
    vertexData = AssignVertexData();
    indices = AssignIndices();

    SetupResources();
    model = glm::translate(model, position);
}
Block::~Block()
{
    delete[] vertexData;
    delete[] indices;
}
std::vector<float>* Block::AssignVertexData()
{
    std::vector<glm::vec3> positions;
    positions.emplace_back(glm::vec3(-1, -1, -1));
    positions.emplace_back(glm::vec3(1, -1, -1));
    positions.emplace_back(glm::vec3(1, 1, -1));
    positions.emplace_back(glm::vec3(-1, 1, -1));
    positions.emplace_back(glm::vec3(-1, -1, 1));
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

    // std::vector<glm::vec3> normals;
    // normals.emplace_back(glm::vec3(-1, -1, -1));
    // normals.emplace_back(glm::vec3(1, -1, -1));
    // normals.emplace_back(glm::vec3(1, 1, -1));
    // normals.emplace_back(glm::vec3(-1, 1, -1));
    // normals.emplace_back(glm::vec3(-1, -1, 1));
    // normals.emplace_back(glm::vec3(1, -1, 1));
    // normals.emplace_back(glm::vec3(-1, -1, -1));
    // normals.emplace_back(glm::vec3(-1, 1, 1));

    std::vector<float>* data = new std::vector<float>();
    data->resize(3 * positions.size() + 2 * uvs.size());
    int offset = 0;
    for (int i = 0; i < positions.size(); i++)
    {
        data->at(offset) = positions[i].x;
        data->at(offset + 1) = positions[i].y;
        data->at(offset + 2) = positions[i].z;

        data->at(offset + 3) = uvs[i].x;
        data->at(offset + 4) = uvs[i].y;

        // data->at(offset + 5) = normals[i].x;
        // data->at(offset + 6) = normals[i].y;
        // data->at(offset + 7) = normals[i].z;
        offset += 5;
    }

    return data;
}
std::vector<unsigned int>* Block::AssignIndices()
{
    std::vector<glm::u8vec3> indices;
    indices.emplace_back(glm::u8vec3(4, 5, 6));
    indices.emplace_back(glm::u8vec3(6, 7, 4));
    indices.emplace_back(glm::u8vec3(0, 6, 2));
    indices.emplace_back(glm::u8vec3(2, 1, 0));
    indices.emplace_back(glm::u8vec3(0, 4, 7));
    indices.emplace_back(glm::u8vec3(7, 3, 0));
    indices.emplace_back(glm::u8vec3(1, 2, 6));
    indices.emplace_back(glm::u8vec3(6, 5, 1));
    indices.emplace_back(glm::u8vec3(3, 7, 6));
    indices.emplace_back(glm::u8vec3(6, 2, 3));
    indices.emplace_back(glm::u8vec3(0, 1, 5));
    indices.emplace_back(glm::u8vec3(5, 4, 0));

    std::vector<unsigned int>* data = new std::vector<unsigned int>();
    data->resize(3 * indices.size());
    int offset = 0;
    for (int i = 0; i < indices.size(); i++)
    {
        data->at(offset) = indices[i].x;
        data->at(offset + 1) = indices[i].y;
        data->at(offset + 2) = indices[i].z;
        offset += 3;
    }
    return data;
}

void Block::SetupResources()
{
    float* vData = vertexData->data();
    unsigned int* iData = indices->data();

    vao.Bind();
    Vbo vbo(vData, vertexData->size() * sizeof(float));
    Ebo ebo(iData, indices->size() * sizeof(unsigned int));
    vao.LinkVbo(vbo);

    vao.UnBind();
    vbo.UnBind();
    ebo.UnBind();

    Texture texture("textures/cool.png");
    texture.Bind();
}
void Block::Draw(Shader& shader)
{
    shader.use();
    vao.Bind();
    shader.setMat4("model", model);
    glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);
}

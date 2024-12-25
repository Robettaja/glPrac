#pragma once

#include "vao.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

enum BlockType
{
    Default = 0,
    Grass,
    Dirt,
    Water,
    Stone,
    Wood,
    Sand,
    Joni,
};

class Block
{
  private:
    BlockType blockType;
    glm::mat4 model;
    Vao vao;
    std::vector<float>* vertexData;
    std::vector<unsigned int>* indices;
    std::vector<float>* AssignVertexData();
    std::vector<unsigned int>* AssignIndices();
    void SetupResources();

  public:
    Block(glm::vec3 position, const char* texturePath);
    ~Block();
    void Draw(Shader& shader);
    void SetActive();
    bool IsActive();
};

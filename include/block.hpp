#pragma once

#include "vao.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Block
{
  private:
    glm::mat4 model;
    Vao vao;
    std::vector<float>* vertexData;
    std::vector<unsigned int>* indices;
    std::vector<float>* AssignVertexData();
    std::vector<unsigned int>* AssignIndices();
    void SetupResources();

  public:
    Block(glm::vec3 position);
    ~Block();
    void Draw();
};

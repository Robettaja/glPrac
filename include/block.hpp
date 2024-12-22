#pragma once

#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Block
{
  private:
    glm::mat4 model;
    float* vertexData;
    unsigned int* indices;
    float* AssignVertexData();
    unsigned int* AssignIndices();
    void SetupResources();

  public:
    Block();
    ~Block();
    void Draw();
};

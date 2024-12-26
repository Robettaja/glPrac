#pragma once

#include "shader.hpp"
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

  public:
    Block();
    ~Block();
    void SetActive();
    bool IsActive();
};

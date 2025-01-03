#pragma once

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

enum BlockType
{
    Default = 0,
    Air,
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
    void SetBlockType(BlockType type);
    bool IsActive();
};

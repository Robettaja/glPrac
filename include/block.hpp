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
    BlockType GetBlockType();
    bool IsActive();
    bool IsSolid();
};

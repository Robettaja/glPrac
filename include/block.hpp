#pragma once

#include <string>

enum class BlockType
{
    Air = 0,
    Grass,
    Stone,
    Sand,
    Dirt,
    Water,
    Wood,
};

class Block
{
  private:
    BlockType blockType;

  public:
    Block();
    ~Block();
    void SetBlockType(BlockType type);
    BlockType GetBlockType() const;
    std::string GetBlockData() const;
    bool IsActive() const;
};

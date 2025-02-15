#pragma once

#include <string>

enum class BlockType
{
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
    void SetBlockType(BlockType type);
    BlockType GetBlockType() const;
    std::string GetBlockData() const;
    bool IsActive() const;
};

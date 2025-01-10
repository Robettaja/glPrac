#include <glad/glad.h>

#include "block.hpp"
#include <string>

#include <glm/fwd.hpp>

Block::Block() : blockType(BlockType::Air)
{
}
Block::~Block() = default;

void Block::SetBlockType(const BlockType type)
{
    blockType = type;
}
BlockType Block::GetBlockType() const
{
    return blockType;
}
bool Block::IsActive() const
{
    return blockType != BlockType::Air;
}
std::string Block::GetBlockData() const
{
    return "Block type: " + std::to_string(static_cast<int>(blockType)) + " " + std::to_string(IsActive());
}

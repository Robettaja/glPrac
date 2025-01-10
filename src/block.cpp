#include <glad/glad.h>

#include "block.hpp"
#include <string>

#include <glm/fwd.hpp>

Block::Block()
{
}
Block::~Block()
{
}
bool Block::IsActive()
{
    return blockType != Air;
}
void Block::SetBlockType(BlockType type)
{
    blockType = type;
}
BlockType Block::GetBlockType()
{
    return blockType;
}
bool Block::IsSolid()
{
    return blockType != Air;
}
std::string Block::GetBlockData()
{
    return "Block type: " + std::to_string(blockType) + " " + std::to_string(IsSolid());
}

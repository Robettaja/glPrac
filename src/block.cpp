#include <glad/glad.h>

#include "block.hpp"

#include <glm/fwd.hpp>

Block::Block()
{
}
Block::~Block()
{
}
bool Block::IsActive()
{
    if (blockType == Air)
        return false;
    return true;
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
    if (blockType == Air || Default)
        return false;
    return true;
}

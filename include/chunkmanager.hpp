#include "chunk.hpp"

class ChunkManager
{
  private:
    Chunk** chunks;

  public:
    void Load();
    void Unload();
};

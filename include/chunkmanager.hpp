#include "chunk.hpp"

class ChunkManager
{
  private:
    std::vector<Chunk*> chunks;

  public:
    void Update();
    void Load();
    void Unload();
};

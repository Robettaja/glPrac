#include "vertex.hpp"
#include <cstdint>
#include <vector>
#include <string>

class ModelLoader
{
  private:
    std::string path;

  public:
    ModelLoader(std::string path);
    std::vector<uint8_t> LoadFBX();
    std::vector<Vertex> GetVertices();
    std::vector<unsigned int> GetIndices();
};

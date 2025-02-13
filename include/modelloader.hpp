#pragma once
#include "mesh.hpp"
#include <string>

class ModelLoader
{
  private:
  public:
    bool IsModeReady = false;
    Mesh LoadModel(std::string filename);
};

#pragma once
#include "vao.hpp"
#include "vertex.hpp"
#include <vector>

class Mesh
{
  private:
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh();
    Mesh(std::vector<Vertex>, std::vector<unsigned int> indices);
    ~Mesh();
    void AddVertices(std::vector<Vertex>& vertexData);
    int GetVertexAmount();
    int GetIndicesAmount();
    void AddIndices(std::vector<unsigned int>& indicesData);
};

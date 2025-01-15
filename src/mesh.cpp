#include "ebo.hpp"
#include "mesh.hpp"
#include "vertex.hpp"
#include <vector>

Mesh::Mesh()
{
}
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;
}
Mesh::~Mesh()
{
}
void Mesh::AddVertices(std::vector<Vertex>& vertexData)
{
    vertices.insert(vertices.end(), vertexData.begin(), vertexData.end());
}
int Mesh::GetVertexAmount()
{
    return vertices.size();
}
int Mesh::GetIndicesAmount()
{
    return indices.size();
}
void Mesh::AddIndices(std::vector<unsigned int>& indicesData)
{
    indices.insert(indices.end(), indicesData.begin(), indicesData.end());
}

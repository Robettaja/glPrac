#pragma once

#include "vao.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include "texture.hpp"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <vector>

class Renderer
{
  private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    glm::mat4 model;
    Vao vao;

  public:
    Renderer(glm::vec3);
    Renderer(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures,
             glm::vec3 pos);
    ~Renderer();
    void LinkRenderData();
    void AddVertices(std::vector<Vertex> vertexData);
    void AddIndices(std::vector<unsigned int> indicesData);
    void Draw(Shader shader);
};

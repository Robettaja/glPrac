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
    explicit Renderer(const glm::vec3&);
    Renderer(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,
             const std::vector<Texture>& textures, glm::vec3 pos);
    ~Renderer();
    void LinkRenderData();
    size_t GetVerticesSize() const;
    void AddVertices(const std::vector<Vertex>& vertexData);
    void AddIndices(const std::vector<unsigned int>& indicesData);
    void SetPosition(glm::vec3 pos);
    void Draw(const Shader& shader) const;
};

#pragma once

#include "vao.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include "texture.hpp"
#include <glm/glm.hpp>
#include <vector>

class Renderer
{
  private:
    glm::mat4 model;
    Vao vao;

  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Renderer(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
    ~Renderer();
    void Draw(Shader& shader, glm::vec3 pos);
};

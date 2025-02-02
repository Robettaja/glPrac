#pragma once

#include "mesh.hpp"
#include "vao.hpp"
#include "shader.hpp"

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <memory>

class Renderer
{
  private:
    Mesh* mesh;
    Vao* vao;

    glm::mat4 model;

  public:
    explicit Renderer(const glm::vec3&);
    ~Renderer();
    void SetPosition(glm::vec3 pos);
    void LinkGL();
    void AddMesh(Mesh& mesh);
    void Draw(const Shader& shader) const;
};

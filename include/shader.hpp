#pragma once

#include "texture.hpp"
#include <string>
#include <glm/glm.hpp>
#include <vector>

class Shader
{
    std::vector<Texture*> textures;

  public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void AddTexture(Texture* texture);
    void use() const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setMat4(const std::string& name, const glm::mat4& value) const;
};

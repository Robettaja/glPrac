#pragma once

#include <vector>
enum textureType
{
    Texture2D,
    texture2DArray
};
class Texture
{

  private:
    textureType type;
    void AddTextureToArray(const char* path, int offset);
    void LoadImageData(const char* path);

  public:
    unsigned int ID = 0;
    int width, height, nrChannels;
    explicit Texture(const char* path, int slot);
    explicit Texture(std::vector<const char*> paths, int slot);
    void Bind() const;
    void Unbind() const;
};

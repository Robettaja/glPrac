#include "texture.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <stb_image.h>
#include <vector>

Texture::Texture(const char* path, int slot)
{
    type = textureType::Texture2D;
    glGenTextures(slot, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Texture::Texture(std::vector<const char*> paths, int slot)
{
    type = textureType::texture2DArray;
    glGenTextures(slot, &ID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_load(paths[0], &width, &height, &nrChannels, STBI_rgb_alpha);

    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 8, GL_RGBA8, width, height, paths.size());

    stbi_set_flip_vertically_on_load(true);
    for (int i = 0; i < paths.size(); i++)
    {
        AddTextureToArray(paths[i], i);
    }

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}
void Texture::AddTextureToArray(const char* path, int offset)
{

    int width, height, nrChannels;
    unsigned char* image = stbi_load(path, &width, &height, &nrChannels, STBI_rgb_alpha);

    if (image)
    {
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, offset, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);
}
void Texture::Bind() const
{
    switch (type)
    {
    case textureType::Texture2D:
        glBindTexture(GL_TEXTURE_2D, ID);
        break;
    case textureType::texture2DArray:

        glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
        break;
    }
}
void Texture::Unbind() const
{
    switch (type)
    {
    case textureType::Texture2D:
        glBindTexture(GL_TEXTURE_2D, 0);
        break;
    case textureType::texture2DArray:

        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
        break;
    }
}

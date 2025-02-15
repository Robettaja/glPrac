#include "texture.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <vector>

Texture::Texture(std::vector<const char*> path)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* firstImg = stbi_load(path[0], &width, &height, &nrChannels, STBI_rgb_alpha);
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 3, GL_RGBA8, width, height, path.size());

    if (firstImg)
    {
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, firstImg);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(firstImg);

    if (path.size() == 1)
        return;

    for (int i = 1; i < path.size(); i++)
    {
        unsigned char* data = stbi_load(path[i], &width, &height, &nrChannels, STBI_rgb_alpha);
        if (data)
        {

            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}
void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
}
void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

#include "modelLoader.hpp"

#include <cstdint>
#include <ofbx.h>
#include <fstream>
#include <iostream>
#include <vector>

ModelLoader::ModelLoader(std::string path)
{
    this->path = path;
}
std::vector<uint8_t> ModelLoader::LoadFBX()
{
    std::ifstream fbxFile(path, std::ios::binary | std::ios::ate);
    if (!fbxFile.is_open())
    {
        std::cout << "Failed to open fbx file" << std::endl;
        return {};
    }
    std::streamsize size = fbxFile.tellg();
    fbxFile.seekg(0, std::ios::beg);
    std::vector<uint8_t> buffer(size);

    std::cout << buffer.size() << std::endl;
    return buffer;
}
std::vector<Vertex> ModelLoader::GetVertices()
{
    std::vector<uint8_t> fbxData = LoadFBX();
    ofbx::LoadFlags loadFlag =
        ofbx::LoadFlags::IGNORE_ANIMATIONS | ofbx::LoadFlags::IGNORE_CAMERAS | ofbx::LoadFlags::IGNORE_BONES;

    const ofbx::IScene* scene = ofbx::load((ofbx::u8*)fbxData.data(), fbxData.size(), (ofbx::u64)loadFlag);
    if (!scene)
    {
        std::cout << "failed to load scene" << "\n";
    }
    // scene->getMeshCount();
    return {};
}

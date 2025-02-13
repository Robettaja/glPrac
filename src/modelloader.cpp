#include "modelloader.hpp"
#include "timer.hpp"
#include <assimp/vector3.h>
#include <glm/fwd.hpp>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Timer timer2("Model Loading timer");

Mesh ModelLoader::LoadModel(std::string filename)
{
    timer2.start();
    Mesh mesh;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_CalcTangentSpace | aiProcess_Triangulate);
    if (scene == nullptr)
    {
        std::cout << "Failed to load model from file " << filename << std::endl;
        return mesh;
    }
    for (int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh* aiMesh = scene->mMeshes[i];
        for (int j = 0; j < aiMesh->mNumVertices; j++)
        {
            aiVector3D aiVertex = aiMesh->mVertices[j];
            glm::vec3 vertexPos(aiVertex.x, aiVertex.y, aiVertex.z);

            aiVector3D uv = aiMesh->mTextureCoords[0][j];
            glm::vec2 uvCoord(uv.x, uv.y);

            aiVector3D normal = aiMesh->mNormals[j];
            glm::vec3 normalVec(normal.x, normal.y, normal.z);

            mesh.vertices.emplace_back(Vertex(vertexPos, uvCoord, normalVec));
        }
        for (int j = 0; j < aiMesh->mNumFaces; j++)
        {
            aiFace aiFace = aiMesh->mFaces[j];
            for (int k = 0; k < aiFace.mNumIndices; k++)
            {
                mesh.indices.emplace_back(aiFace.mIndices[k]);
            }
        }
    }
    timer2.stop();
    return mesh;
}

#ifndef MY_MODEL_H_
#define MY_MODEL_H_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "myMesh.h"
class myMesh;
#include "Texture.h"

#include <iostream>
#include <memory>
#include "pVector.h"

class myModel
{
    private:
        // model data
        std::vector<std::shared_ptr<myMesh>> m_meshes;
        std::string m_directory;
        std::vector<std::shared_ptr<Texture>> m_texturesLoaded;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        std::shared_ptr<myMesh> processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial *mat,
                                                                    aiTextureType type,
                                                                    std::string typeName);
    public:
        inline const std::vector<std::shared_ptr<myMesh>> getMeshes() const { return m_meshes; }
        std::vector<FlatVector> getVectorOfVertices();
        myModel(const std::string& path);
};

#endif // MY_MODEL_H_

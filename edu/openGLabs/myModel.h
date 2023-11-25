#ifndef MY_MODEL_H_
#define MY_MODEL_H_

#define MULTI_THREADING 1

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "myMesh.h"
class myMesh;
#include "Texture.h"
#include "loader.h"
#include <iostream>
#include <memory>

class myModel : public v::Loadable
{
    private:
        // model data
        std::string m_fullPath;
        std::string m_directory;
        std::vector<std::shared_ptr<myMesh>> m_meshes;
        void Load() override;
        void processNode(aiNode *node, const aiScene *scene);
        void processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture*> loadMaterialTextures(aiMaterial *mat,
                                                                    aiTextureType type,
                                                                    std::string typeName);
    public:
        void Draw(Shader& shader) const;
        explicit myModel(const std::string& path);
};

#endif // MY_MODEL_H_

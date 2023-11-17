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
        std::vector<std::shared_ptr<Texture>> m_texturesLoaded;
        const aiScene *m_scene;
        void Load() override;
        void processNode(aiNode *node);
        void processMesh(aiMesh *mesh);
        std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial *mat,
                                                                    aiTextureType type,
                                                                    std::string typeName);
    public:
        inline const std::vector<std::shared_ptr<myMesh>> getMeshes() const { return m_meshes; }
        myModel(const std::string& path);
};

#endif // MY_MODEL_H_

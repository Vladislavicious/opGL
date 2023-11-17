#include "myModel.h"
myModel::myModel(const std::string& path):
    m_fullPath(path)
{
    v::Loader::addToLoadQueue(this);
}

void myModel::Load()
{
    Assimp::Importer importer;
    m_scene = importer.ReadFile(m_fullPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    m_directory = m_fullPath.substr(0, m_fullPath.find_last_of('/'));

    processNode(m_scene->mRootNode);
    std::cout << "loaded" << std::endl;
    m_scene = nullptr;
    v::Loadable::Load();
}

void myModel::processNode(aiNode *node)
{
    // process all the node's meshes (if any)
    for(unsigned int j = 0; j < node->mNumMeshes; j++)
    {
        aiMesh *mesh = m_scene->mMeshes[node->mMeshes[j]];
        processMesh(mesh);
    }
    // then do the same for each of its children
    for(unsigned int j = 0; j < node->mNumChildren; j++)
    {
        processNode(node->mChildren[j]);
    }
}

void myModel::processMesh(aiMesh *mesh)
{
    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);
    std::vector<unsigned int> indices;
    indices.reserve(mesh->mNumFaces * 3);
    std::vector<std::shared_ptr<Texture>> textures;
    textures.reserve(2);

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);


        vertices.push_back(vertex);
    }
    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process material
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = m_scene->mMaterials[mesh->mMaterialIndex];
        std::vector<std::shared_ptr<Texture>> diffuseMaps = loadMaterialTextures(material,
                                            aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<std::shared_ptr<Texture>> specularMaps = loadMaterialTextures(material,
                                            aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    m_meshes.push_back(std::make_shared<myMesh>(std::move(vertices), std::move(indices), std::move(textures)));
}

std::vector<std::shared_ptr<Texture>> myModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                        std::string typeName)
{
    std::vector<std::shared_ptr<Texture>> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        auto fullPath = m_directory + "/" + str.C_Str();
        bool skip = false;
        for(unsigned int j = 0; j < m_texturesLoaded.size(); j++)
        {
            if(std::strcmp(m_texturesLoaded[j]->getPath().data(), fullPath.c_str()) == 0)
            {
                textures.push_back(m_texturesLoaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            auto texture = std::make_shared<Texture>(fullPath, typeName);
            textures.push_back(texture);
            m_texturesLoaded.push_back(texture); // add to loaded textures
        }
    }
    return textures;
}

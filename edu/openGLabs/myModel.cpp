#include "myModel.h"

void myModel::Draw(Shader& shader) const
{
    if(!v::Loadable::IsLoaded())
        return;

    for (const auto& mesh : m_meshes)
    {
        mesh.Draw(shader);
    }
}

myModel::myModel(const std::string &path) : m_fullPath(path)
{
    v::Loader::addToLoadQueue(this);
}

void myModel::Load()
{
    Assimp::Importer importer;
    auto scene = importer.ReadFile(m_fullPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    m_directory = m_fullPath.substr(0, m_fullPath.find_last_of('/'));
    auto root = scene->mRootNode;
    m_meshes.reserve(root->mNumMeshes);
    processNode(root, scene);
    std::cout << "loaded" << std::endl;
    v::Loadable::Load();
}

void myModel::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int j = 0; j < node->mNumMeshes; j++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[j]];
        processMesh(mesh, scene);
    }
    // then do the same for each of its children
    for(unsigned int j = 0; j < node->mNumChildren; j++)
    {
        processNode(node->mChildren[j], scene);
    }
}

void myModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    vertices.reserve(mesh->mNumVertices);
    std::vector<unsigned int> indices;
    indices.reserve(mesh->mNumFaces * 3);
    std::vector<Texture*> textures;
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
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture*> diffuseMaps = loadMaterialTextures(material,
                                            aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture*> specularMaps = loadMaterialTextures(material,
                                            aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    m_meshes.emplace_back(std::move(vertices), std::move(indices), std::move(textures));
}

std::vector<Texture*> myModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                        std::string typeName)
{
    std::vector<Texture*> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        auto fullPath = m_directory + "/" + str.C_Str();
        textures.push_back(Texture::getTexture(fullPath, typeName));
    }
    return textures;
}

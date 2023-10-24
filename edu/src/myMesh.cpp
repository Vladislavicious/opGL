#include "myMesh.h"

myMesh::myMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    m_VertexArray = new VertexArray();
    m_IndexBuffer = nullptr;
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;
    setupMesh();
}

myMesh::~myMesh()
{
    delete m_VertexArray;
    delete m_IndexBuffer;
}

void myMesh::setupMesh()
{
    VertexBufferLayout vbLayout;
    vbLayout.Push<float>(3); // 3 координаты
    vbLayout.Push<float>(3); // 3 нормали
    vbLayout.Push<float>(2); // 2 текстурных координаты

    auto Buffer = VertexBuffer(m_vertices);
    m_VertexArray->AddBuffer(Buffer, vbLayout);
    m_IndexBuffer = new IndexBuffer(&m_indices[0], m_indices.size());
}

void myMesh::Draw(Renderer &renderer, Shader &shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < m_textures.size(); i++)
    {
        m_textures[i].bind(i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = m_textures[i].getType();
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.SetUniform1i(("material." + name + number).c_str(), i);
    }
    renderer.Draw(*m_VertexArray, *m_IndexBuffer, shader);
}

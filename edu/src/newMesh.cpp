#include "newMesh.h"

newMesh::newMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures):
   m_VertexArray(new VertexArray()), m_IndexBuffer(new IndexBuffer(indices))
{
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;
    VertexBufferLayout vbLayout;
    vbLayout.Push<float>(3); // 3 координаты
    vbLayout.Push<float>(3); // 3 нормали
    vbLayout.Push<float>(2); // 2 текстурных координаты

    auto Buffer = VertexBuffer(m_vertices);
    m_VertexArray->AddBuffer(Buffer, vbLayout);
}

newMesh::~newMesh()
{
    delete m_VertexArray;
    delete m_IndexBuffer;
}

void newMesh::Bind() const
{
    m_VertexArray->Bind();
    m_IndexBuffer->Bind();
}
void newMesh::UnBind() const
{
    m_VertexArray->UnBind();
    m_IndexBuffer->UnBind();
}

#include "newMesh.h"

newMesh::newMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures):
    m_vertices(vertices), m_indices(indices), m_textures(textures),
    m_VertexArray(new VertexArray(m_vertices)), m_IndexBuffer(new IndexBuffer(m_indices))
{
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

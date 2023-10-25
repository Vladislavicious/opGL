#include "myMesh.h"

myMesh::myMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<std::shared_ptr<Texture>> textures):
    m_vertices(vertices), m_indices(indices), m_textures(textures),
    m_VertexArray(new VertexArray(m_vertices)), m_IndexBuffer(new IndexBuffer(m_indices))
{
}

myMesh::~myMesh()
{
   delete m_VertexArray;
   delete m_IndexBuffer;
}

void myMesh::Bind() const
{
    m_VertexArray->Bind();
    m_IndexBuffer->Bind();
}
void myMesh::UnBind() const
{
    m_VertexArray->UnBind();
    m_IndexBuffer->UnBind();
}

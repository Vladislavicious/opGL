#include "myMesh.h"

myMesh::myMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,
           const std::vector<Texture*>& m_textures):
    m_vertices(vertices), m_indices(indices), m_textures(m_textures),
    m_VertexArray(new VertexArray(m_vertices)), m_IndexBuffer(m_indices)
{
}

myMesh::myMesh(myMesh &&other) noexcept
    : m_vertices(std::move(other.m_vertices)), m_indices(std::move(other.m_indices)),
    m_textures(std::move(other.m_textures)), m_VertexArray(std::move(other.m_VertexArray)),
    m_IndexBuffer(std::move(other.m_IndexBuffer))
{
}

myMesh::~myMesh()
{
    delete m_VertexArray;
}

void myMesh::Bind() const
{
    m_VertexArray->Bind();
    m_IndexBuffer.Bind();
}
void myMesh::UnBind() const
{
    m_VertexArray->UnBind();
    m_IndexBuffer.UnBind();
}

void myMesh::Draw(Shader &shader) const
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    shader.Bind();
    for(unsigned int i = 0; i < m_textures.size(); i++)
    {
        m_textures[i]->bind(i);
        std::string number;
        std::string name = m_textures[i]->getType();
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        m_textures[i]->bind(i);
        shader.SetUniform1i(("material." + name + number).c_str(), i);
    }

    auto renderer = Renderer::getInstance();
    renderer->Draw(this, shader);
}

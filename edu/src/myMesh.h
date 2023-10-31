#ifndef NEW_MESH_H_
#define NEW_MESH_H_
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexBufferLayout.h"
class VertexBufferLayout;
#include "VertexArray.h"
class VertexArray;
#include "VertexBuffer.h"
class VertexBuffer;
#include "IndexBuffer.h"
class IndexBuffer;
#include "Texture.h"
#include "Shader.h"
#include "myVertex.h"
#include <memory>

class myMesh {
    private:
        std::vector<Vertex>                    m_vertices;
        std::vector<unsigned int>              m_indices;
        std::vector<std::shared_ptr<Texture>>  m_textures;
        VertexArray*                           m_VertexArray;
		IndexBuffer*                           m_IndexBuffer;
    public:
        inline std::vector<Vertex> getVertexes() const { return m_vertices; }
        inline std::vector<std::shared_ptr<Texture>> getTextures() const { return m_textures; }
        inline unsigned int getCount() const { return m_IndexBuffer->GetCount(); }
        void Bind() const;
	    void UnBind() const;
        myMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
                std::vector<std::shared_ptr<Texture>> textures);
        ~myMesh();
};

#endif // MY_MESH_H_

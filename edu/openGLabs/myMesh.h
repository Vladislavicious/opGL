#ifndef NEW_MESH_H_
#define NEW_MESH_H_
#include <memory>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexArray.h"
class VertexArray;
#include "Texture.h"
#include "Shader.h"
#include "myVertex.h"

class myMesh {
    private:
        std::vector<Vertex>                     m_vertices;
        std::vector<unsigned int>               m_indices;
        std::vector<Texture*>                   m_textures;
        VertexArray*                            m_VertexArray;
		IndexBuffer                             m_IndexBuffer;
    public:
        inline std::vector<Vertex> getVertexes() const { return m_vertices; }
        inline unsigned int getCount() const { return m_IndexBuffer.GetCount(); }
        void Bind() const;
	    void UnBind() const;
        void Draw(Shader& shader) const;
        myMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices,
           const std::vector<Texture*>& m_textures);
        myMesh(const myMesh& other) = delete;
        myMesh(myMesh&& other) noexcept;
        myMesh operator=(const myMesh& other) = delete;
        ~myMesh();
};

#endif // MY_MESH_H_

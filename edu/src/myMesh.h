#ifndef MY_MESH_H_
#define MY_MESH_H_
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
class Renderer;
#include "VertexBufferLayout.h"
#include "VertexArray.h"
class VertexArray;
#include "IndexBuffer.h"
class IndexBuffer;
#include "Texture.h"
#include "Shader.h"

struct Vertex {
    glm::vec4 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class myMesh {
    private:
        //  render data
        VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
        // mesh data
        std::vector<Vertex>       m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<Texture>      m_textures;

        void setupMesh();
    public:
        myMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        ~myMesh();
        void Draw(Renderer &renderer, Shader &shader);
};

#endif // MY_MESH_H_

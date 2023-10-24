#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW
#include "Renderer.h"
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum currentError = glGetError())
    {
        std::cout << "[OpenGL error]: " << currentError << " occured in " << function << " in " << file <<
            " on line: " << line << std::endl;
        return false;
    }
    return true;
}


void Renderer::Clear() const
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const
{
    shader.Bind();
    vertexArray.Bind();
    indexBuffer.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::Draw(const newMesh &mesh, Shader &shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    shader.Bind();
    for(unsigned int i = 0; i < mesh.getTextures().size(); i++)
    {
        mesh.getTextures()[i].bind(i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = mesh.getTextures()[i].getType();
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        mesh.getTextures()[i].bind(i);
        shader.SetUniform1i(("material." + name + number).c_str(), i);
    }
    shader.Bind();
    mesh.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, mesh.getCount(), GL_UNSIGNED_INT, nullptr));
}

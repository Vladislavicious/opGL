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
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, GLenum mode) const
{
    shader.Bind();
    vertexArray.Bind();
    indexBuffer.Bind();

    GLCall(glDrawElements(mode, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));

}
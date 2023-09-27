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

void Renderer::Draw(const VertexArray& vertexArray, const Shader& shader, int count) const
{

    shader.Bind();
    vertexArray.Bind();
    glLineWidth(10.0f);

    GLCall(glDrawArrays(GL_TRIANGLE_STRIP, 0, count));

}

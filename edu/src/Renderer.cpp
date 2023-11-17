#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW
#include "Renderer.h"
void GLClearError(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
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

Renderer* Renderer::instancePtr = nullptr;

Renderer::Renderer()
{
    GLCall(glEnable(GL_DEPTH_TEST));
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

void Renderer::Draw(const myMesh &mesh, Shader &shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    shader.Bind();
    auto textures = mesh.getTextures();
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        textures[i]->bind(i);
        std::string number;
        std::string name = textures[i]->getType();
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        textures[i]->bind(i);
        shader.SetUniform1i(("material." + name + number).c_str(), i);
    }
    mesh.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, mesh.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const myModel &model, Shader &shader)
{
    for (auto& mesh : model.getMeshes())
        Draw(*mesh, shader);
}

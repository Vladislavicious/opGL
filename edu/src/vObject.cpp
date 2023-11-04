#include "vObject.h"

namespace v
{


    Object::Object(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath):
        m_pos(position), m_size(size), m_model(new myModel(filePath)),
        m_shader(new Shader(vsShaderPath, fsShaderPath)), m_renderer(Renderer::getInstance())
    {
    }

    glm::mat4 Object::createModelMatrix()
    {
        auto model = glm::translate(glm::mat4(1.0f), m_pos);
        model = glm::scale(model, glm::vec3(m_size));
        return model;
    }

    void Object::ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix)
    {
        auto model = createModelMatrix();
        m_shader->Bind();
        m_shader->SetUniformMat4f("model", model);
        m_shader->SetUniformMat4f("view", viewMatrix);
        m_shader->SetUniformMat4f("projection", projMatrix);
    }

    void Object::Draw()
    {
        m_renderer = Renderer::getInstance();
        m_renderer->Draw(*m_model, *m_shader);
    }
}

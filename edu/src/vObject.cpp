#include "vObject.h"

namespace v
{
    Object::Object(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath,
                std::shared_ptr<Renderer> renderer):
        m_pos(position), m_size(size), m_model(new myModel(filePath)),
        m_shader(new Shader(vsShaderPath, fsShaderPath)), m_renderer(renderer)
    {
    }

    void Object::ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix) const
    {
        auto model = glm::translate(glm::mat4(1.0f), m_pos);
        model = glm::scale(model, glm::vec3(m_size));
        m_shader->Bind();
        m_shader->SetUniformMat4f("model", model);
        m_shader->SetUniformMat4f("view", viewMatrix);
        m_shader->SetUniformMat4f("projection", projMatrix);
        m_shader->SetUniform3f("colour", glm::vec3(0.6f));
    }

    void Object::Draw() const
    {
        m_renderer->Draw(*m_model, *m_shader);
    }
}

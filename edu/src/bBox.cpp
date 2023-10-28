#include "bBox.h"

bBox::bBox(glm::vec3 position, glm::vec3 size, const std::string& vsShaderPath,
         const std::string& fsShaderPath):
    m_pos(position), m_size(size), m_model(new myModel("../edu/res/cube/cube.obj")),
    m_shader(new Shader(vsShaderPath, fsShaderPath))
{
}

bBox::~bBox()
{
    delete m_model;
    delete m_shader;
}

void bBox::ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix) const
{
    auto model = glm::translate(glm::mat4(1.0f), m_pos);
    model = glm::scale(model, glm::vec3(m_size));
    m_shader->Bind();
    m_shader->SetUniformMat4f("model", model);
    m_shader->SetUniformMat4f("view", viewMatrix);
    m_shader->SetUniformMat4f("projection", projMatrix);
    m_shader->SetUniform3f("colour", glm::vec3(0.6f));
}

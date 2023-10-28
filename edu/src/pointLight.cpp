#include "pointLight.h"

PointLight::PointLight(glm::vec3 lightPos, glm::vec3 ambient, glm::vec3 diffuse,
                glm::vec3 specular, float constant, float linear,
                float quadratic, float scale, const std::string& vsShaderPath,
                const std::string& fsShaderPath):
        m_lightPos(lightPos), m_ambient(ambient), m_diffuse(diffuse), m_specular(specular),
        m_constant(constant), m_linear(linear), m_quadratic(quadratic),
        m_scale(scale)
{
    m_lightModel = new myModel("../edu/res/cube/cube.obj");
    m_lightShader = new Shader(vsShaderPath, fsShaderPath);
}

PointLight::~PointLight()
{
    delete m_lightModel;
    delete m_lightShader;
}

void PointLight::ToObjectShader(Shader& shader, const std::string& prefix) const
{
    shader.SetUniform3f(prefix + ".position",  m_lightPos);
    shader.SetUniform3f(prefix + ".ambient",  m_ambient);
    shader.SetUniform3f(prefix + ".diffuse",  m_diffuse);
    shader.SetUniform3f(prefix + ".specular",  m_specular);
    shader.SetUniform1f(prefix + ".constant",  m_constant);
    shader.SetUniform1f(prefix + ".linear",    m_linear);
    shader.SetUniform1f(prefix + ".quadratic", m_quadratic);
}

void PointLight::ToLightShader(glm::mat4& viewMatrix, glm::mat4& projMatrix) const
{
    auto lightModel = glm::translate(glm::mat4(1.0f), m_lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(m_scale));
    m_lightShader->Bind();
    m_lightShader->SetUniformMat4f("model", lightModel);
    m_lightShader->SetUniformMat4f("view", viewMatrix);
    m_lightShader->SetUniformMat4f("projection", projMatrix);
    m_lightShader->SetUniform3f("colour", m_diffuse);
}

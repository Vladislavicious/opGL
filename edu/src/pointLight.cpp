#include "pointLight.h"
namespace v
{
    PointLight::PointLight(glm::vec3 position, glm::vec3 size, glm::vec3 ambient, glm::vec3 diffuse,
                    glm::vec3 specular, float constant, float linear,
                    float quadratic, const std::string& filePath,
                    const std::string& vsShaderPath, const std::string& fsShaderPath):
            Object(position, size, filePath, vsShaderPath, fsShaderPath),
            Light(ambient, diffuse, specular), m_constant(constant),
            m_linear(linear), m_quadratic(quadratic)
    {
    }

    PointLight::~PointLight()
    {
    }

    void PointLight::ToObjectShader(Shader& shader, const std::string& prefix) const
    {
        shader.SetUniform3f(prefix + ".position",  m_pos);
        shader.SetUniform3f(prefix + ".ambient",  m_ambient);
        shader.SetUniform3f(prefix + ".diffuse",  m_diffuse);
        shader.SetUniform3f(prefix + ".specular",  m_specular);
        shader.SetUniform1f(prefix + ".constant",  m_constant);
        shader.SetUniform1f(prefix + ".linear",    m_linear);
        shader.SetUniform1f(prefix + ".quadratic", m_quadratic);
    }

    void PointLight::ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix)
    {
        Object::ToDrawShader(viewMatrix, projMatrix);
        m_shader.SetUniform3f("colour", m_diffuse);
    }


    /*           SPOTLIGHT             */

    SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse,
                glm::vec3 specular, float constant, float linear,
                float quadratic, float cutOff, float outerCutOff):
                Light(ambient, diffuse, specular), m_lightPosition(position), m_lightDirection(direction),
                m_constant(constant), m_linear(linear), m_quadratic(quadratic),
                m_cutOff(cutOff), m_outerCutOff(outerCutOff)
    {
    }

    void SpotLight::ToObjectShader(Shader& shader, const std::string& prefix) const
    {
        shader.SetUniform3f(prefix + ".position",  m_lightPosition);
        shader.SetUniform3f(prefix + ".direction",  m_lightDirection);
        shader.SetUniform3f(prefix + ".ambient",  m_ambient);
        shader.SetUniform3f(prefix + ".diffuse",  m_diffuse);
        shader.SetUniform3f(prefix + ".specular",  m_specular);
        shader.SetUniform1f(prefix + ".constant",  m_constant);
        shader.SetUniform1f(prefix + ".linear",    m_linear);
        shader.SetUniform1f(prefix + ".quadratic", m_quadratic);
        shader.SetUniform1f(prefix + ".cutOff", glm::cos(glm::radians(m_cutOff)));
        shader.SetUniform1f(prefix + ".outerCutOff", glm::cos(glm::radians(m_outerCutOff)));
    }
}

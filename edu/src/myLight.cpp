#include "myLight.h"
namespace v
{
    Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular):
            m_ambient(ambient), m_diffuse(diffuse), m_specular(specular)
    {
    }

    void Light::ToObjectShader(Shader& shader, const std::string& prefix) const
    {
        shader.SetUniform3f(prefix + ".ambient",  m_ambient);
        shader.SetUniform3f(prefix + ".diffuse",  m_diffuse);
        shader.SetUniform3f(prefix + ".specular",  m_specular);
    }


    /*         DirLight             */
    DirLight::DirLight(glm::vec3 ambient, glm::vec3 diffuse,
                        glm::vec3 specular, glm::vec3 direction)
                : Light(ambient, diffuse, specular), m_direction(direction)
    {
    }

    void DirLight::ToObjectShader(Shader& shader, const std::string& prefix) const
    {
        shader.SetUniform3f(prefix + ".direction",  m_direction);
        Light::ToObjectShader(shader, prefix);
    }


}

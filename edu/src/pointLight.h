#ifndef _POINT_LIGHT_H
#define _POINT_LIGHT_H
#include "Shader.h"
#include "myModel.h"
#include "vObject.h"
#include "myLight.h"

namespace v
{
    class PointLight : public Object, public Light
    {
    private:
        float m_constant;
        float m_linear;
        float m_quadratic;
    public:
        PointLight(glm::vec3 position, glm::vec3 size, glm::vec3 ambient, glm::vec3 diffuse,
                    glm::vec3 specular, float constant, float linear,
                    float quadratic, const std::string& filePath,
                    const std::string& vsShaderPath, const std::string& fsShaderPath);
        ~PointLight() override;
        void ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix) override;
        void ToObjectShader(Shader& shader, const std::string& prefix) const override;
    };

    class SpotLight : public Light
    {
    private:
        glm::vec3 m_lightPosition;
        glm::vec3 m_lightDirection;

        float m_constant;
        float m_linear;
        float m_quadratic;
        float m_cutOff;
        float m_outerCutOff;
    public:
        SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse,
                glm::vec3 specular, float constant, float linear,
                float quadratic, float cutOff, float outerCutOff);
        void ToObjectShader(Shader& shader, const std::string& prefix) const override;
        void setLightDirection(glm::vec3 direction) { m_lightDirection = direction; }
        void setLightPosition(glm::vec3 position) { m_lightPosition = position; }
    };
}

#endif // _POINT_LIGHT_H

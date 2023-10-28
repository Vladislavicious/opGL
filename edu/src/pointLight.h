#ifndef _POINT_LIGHT_H
#define _POINT_LIGHT_H
#include "Shader.h"
#include "myModel.h"

class PointLight
{
private:
    glm::vec3 m_lightPos;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    float m_constant;
    float m_linear;
    float m_quadratic;
    float m_scale;

    Shader* m_lightShader;
    myModel* m_lightModel;
public:
    PointLight(glm::vec3 lightPos, glm::vec3 ambient, glm::vec3 diffuse,
                glm::vec3 specular, float constant, float linear,
                float quadratic, float scale, const std::string& vsShaderPath,
                const std::string& fsShaderPath);
    ~PointLight();
    void ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix) const;
    void ToObjectShader(Shader& shader, const std::string& prefix) const;
    glm::vec3& getLightPos() { return m_lightPos; }
    glm::vec3& getLightColor() { return m_diffuse; }
    const myModel& getModel() { return *m_lightModel; }
    Shader& getShader() { return *m_lightShader; }
};

#endif // _POINT_LIGHT_H

#ifndef _LIGHT_H
#define _LIGHT_H
#include "Shader.h"
#include "myModel.h"
#include "vObject.h"

namespace v
{
    class Light
    {
    protected:
        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
    public:
        Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
        virtual ~Light() {}
        virtual void ToObjectShader(Shader& shader, const std::string& prefix) const;
        virtual glm::vec3& getLightColor() { return m_diffuse; }
        virtual void setLightColor(glm::vec3 color) { m_diffuse = color; }
    };

    class DirLight : public Light
    {
    private:
        glm::vec3 m_direction;
    public:
        DirLight(glm::vec3 ambient, glm::vec3 diffuse,
                 glm::vec3 specular, glm::vec3 direction);
        void ToObjectShader(Shader& shader, const std::string& prefix) const override;
    };
}

#endif // _LIGHT_H

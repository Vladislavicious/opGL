#ifndef _B_BOX_H
#define _B_BOX_H

#include "Shader.h"
#include "myModel.h"

namespace v
{
    class Object
    {
    protected:
        glm::vec3 m_pos;
        glm::vec3 m_size;
        glm::vec3 m_rotation;

        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<myModel> m_model;
        std::shared_ptr<Renderer> m_renderer;
    public:
        Object(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath,
                std::shared_ptr<Renderer> renderer);
        virtual ~Object() {}
        virtual void ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix);
        virtual void Draw() const;
        virtual glm::vec3& getSize() { return m_size; }
        virtual glm::vec3& getPos() { return m_pos; }
        virtual void setPos(glm::vec3 position) { m_pos = position; }
        virtual void addVelVec(float x, float y, float z) { m_pos += glm::vec3(x, y, z); }
        virtual void addRotation(float x, float y, float z) { m_rotation += glm::vec3(x, y, z); }
        virtual const myModel& getModel() { return *m_model; }
        virtual Shader& getShader() { return *m_shader; }
    };
}

#endif // _B_BOX_H

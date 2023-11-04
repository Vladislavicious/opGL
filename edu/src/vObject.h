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

        std::shared_ptr<Shader> m_shader;
        std::unique_ptr<myModel> m_model;
        Renderer* m_renderer;
        virtual glm::mat4 createModelMatrix();
    public:
        Object(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath);
        virtual ~Object() {}
        virtual void ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix);
        virtual void Draw();
        virtual glm::vec3& getSize() { return m_size; }
        virtual glm::vec3& getPos() { return m_pos; }
        virtual void setPos(glm::vec3 position) { m_pos = position; }
        virtual void addVelVec(float x, float y, float z) { m_pos += glm::vec3(x, y, z); }
        virtual const myModel& getModel() { return *m_model; }
        virtual std::shared_ptr<Shader> getShader() { return m_shader; }
    };
}

#endif // _B_BOX_H

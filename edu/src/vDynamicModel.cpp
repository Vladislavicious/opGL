#include "vDynamicModel.h"
#include "pPhysicsScene.h"

namespace v
{
    DynamicModel::DynamicModel(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath):
        Object(position, size, filePath, vsShaderPath, fsShaderPath), m_bBox(nullptr)
    {
    }

    glm::mat4 DynamicModel::createModelMatrix()
    {
        glm::mat4 model;
        if (m_bBox)
        {
            model = m_bBox->getNonScaledModelMatrix();
            model = glm::scale(model, m_size);
        }
        else
        {
            model = Object::createModelMatrix();
        }
        return model;
    }

    void DynamicModel::addBoundBox(glm::vec3 relatedPosition, glm::vec3 size, bool isStatic)
    {
        if (m_bBox)
            std::cout << "переопределение bBox'a еще не сделано\n";
        auto scene = v::PhysicScene::getInstance();
        m_bBox = scene->getBbox(m_pos + relatedPosition, size, isStatic);
    }

    void DynamicModel::ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix)
    {
        Object::ToDrawShader(viewMatrix, projMatrix);
    }

    void DynamicModel::Draw()
    {
        Object::Draw();
    }
}

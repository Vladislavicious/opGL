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
        if (m_bBox != nullptr)
        {
            model = m_bBox->getNonScaledModelMatrix();
            model = glm::scale(model, m_size);
            auto vec = m_bBox->getPos();
            setPos(vec);
        }
        else
        {
            model = Object::createModelMatrix();
        }
        return model;
    }

    void DynamicModel::addBoundBox(glm::vec3 relatedPosition, glm::vec3 size, bool isStatic,
                                bool lockAxisX, bool lockAxisY, bool lockAxisZ)
    {
        if (m_bBox != nullptr)
            std::cout << "переопределение bBox'a еще не сделано\n";
        auto scene = v::PhysicScene::getInstance();
        m_bBox = scene->getBbox(m_pos + relatedPosition, size, isStatic, lockAxisX, lockAxisY, lockAxisZ);
    }

    void DynamicModel::deleteBoundBox()
    {
        auto scene = v::PhysicScene::getInstance();
        scene->deleteBbox(m_bBox);
        m_bBox = nullptr;
    }
}

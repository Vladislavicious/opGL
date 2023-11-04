#include "pPhysicsScene.h"

namespace v
{
    glm::vec3 vec3FromQvec3(q3Vec3 vector) { return glm::vec3(vector.x, vector.y, vector.z); }
    q3Vec3 qVec3FromVec3(glm::vec3 vector) { return q3Vec3(vector.x, vector.y, vector.z); }

    PhysicScene* PhysicScene::instancePtr = nullptr;

    v::boundBox* PhysicScene::getBbox(q3Vec3 positon, q3Vec3 size, bool isStatic)
    {
        auto pos = vec3FromQvec3(positon);
        auto siz = vec3FromQvec3(size);
        return getBbox(pos, siz, isStatic);
    }

    v::boundBox* PhysicScene::getBbox(glm::vec3 positon, glm::vec3 size, bool isStatic)
    {
        auto bBox = new v::boundBox(positon, size, m_scene, isStatic);
        m_bBoxes.push_back(bBox);
        return bBox;
    }

    PhysicScene::PhysicScene()
        : m_scene(std::make_shared<q3Scene>( 1.0 / 60.0 ))
    {
        m_scene->SetGravity(q3Vec3(0.0f, -1.0f, 0.0f));
    }

    void PhysicScene::ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix)
    {
        for (auto bBox : m_bBoxes)
        {
            bBox->ToDrawShader(viewMatrix, projMatrix);
        }
    }

    void PhysicScene::Draw()
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(3.0f);
        for (auto bBox : m_bBoxes)
        {
            bBox->Draw();
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }



} // namespace v

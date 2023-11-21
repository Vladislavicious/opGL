#include "pPhysicsScene.h"

namespace v
{
    glm::vec3 vec3FromQvec3(q3Vec3 vector) { return glm::vec3(vector.x, vector.y, vector.z); }
    q3Vec3 qVec3FromVec3(glm::vec3 vector) { return q3Vec3(vector.x, vector.y, vector.z); }

    PhysicScene* PhysicScene::instancePtr = nullptr;

    std::shared_ptr<v::boundBox> PhysicScene::getBbox(q3Vec3 positon, q3Vec3 size, bool isStatic,
                                                    bool lockAxisX, bool lockAxisY, bool lockAxisZ)
    {
        auto pos = vec3FromQvec3(positon);
        auto siz = vec3FromQvec3(size);
        return getBbox(pos, siz, isStatic, lockAxisX, lockAxisY, lockAxisZ);
    }

    std::shared_ptr<v::boundBox> PhysicScene::getBbox(glm::vec3 positon, glm::vec3 size, bool isStatic,
                                                    bool lockAxisX, bool lockAxisY, bool lockAxisZ)
    {
        auto temp = std::make_shared<v::boundBox>(positon, size, m_scene, isStatic, lockAxisX, lockAxisY, lockAxisZ);
        m_bBoxes.push_back(temp);
        return temp;
    }

    void PhysicScene::deleteBbox(std::shared_ptr<v::boundBox> box)
    {
        deleteBbox(box.get());
    }

    void PhysicScene::deleteBbox(const v::Object* box)
    {
        bool found = false;
        auto item = m_bBoxes.begin();
        for (; item != m_bBoxes.end(); item++)
        {
            if ( item->get() == box )
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            remove(item);
        }
    }

    void PhysicScene::deleteBbox(const q3Body* body)
    {
        bool found = false;
        auto item = m_bBoxes.begin();
        for (; item != m_bBoxes.end(); item++)
        {
            auto ptr = *item;
            if ( ptr->getBody() == body )
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            remove(item);
        }
    }

    void PhysicScene::remove(std::vector<std::shared_ptr<v::boundBox>>::iterator it)
    {
        m_scene->RemoveBody(it->get()->getBody());
        m_bBoxes.erase(it);
    }

    PhysicScene::PhysicScene()
        : frameTime(1.0f / 60.0f), m_scene(std::make_shared<q3Scene>(frameTime))
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

    void PhysicScene::addWorldBorder(float Width)
    {
        float planeWidth = 1.0f;
        getBbox(glm::vec3(0.0f), glm::vec3(Width, planeWidth, Width), true);
        getBbox(glm::vec3(0.0f, Width + planeWidth, Width + planeWidth),
                        glm::vec3(Width, Width, planeWidth), true);
        getBbox(glm::vec3(0.0f, Width + planeWidth, -Width - planeWidth),
                        glm::vec3(Width, Width, planeWidth), true);
        auto temp = getBbox(glm::vec3(Width + planeWidth, Width + planeWidth, 0.0f),
                        glm::vec3(Width, Width, planeWidth), true);
        temp->rotateY(90.0f);
        temp = getBbox(glm::vec3(-Width - planeWidth, Width + planeWidth, 0.0f),
                        glm::vec3(Width, Width, planeWidth), true);
        temp->rotateY(90.0f);
        temp = getBbox(glm::vec3(0.0f, 2 * Width + planeWidth * 2, 0.0f), glm::vec3(Width, Width, planeWidth), true);
        temp->rotateX(90.0f);
    }

    void PhysicScene::Dump(q3Body *body)
    {
        std::FILE* fp = fopen( "../body.txt.log", "w" );
        body->Dump(fp, 0);
        fclose(fp);
    }

} // namespace v

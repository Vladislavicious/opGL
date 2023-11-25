#ifndef _PHYS_SCENE_H
#define _PHYS_SCENE_H

#include "src/q3.h"
#include "vBoundBox.h"
#include <memory>
namespace v
{
    class PhysicScene
    {
    private:
        const float frameTime;
        static PhysicScene* instancePtr;

        std::shared_ptr<q3Scene> m_scene;
        std::vector<std::shared_ptr<v::boundBox>> m_bBoxes;
        void remove(std::vector<std::shared_ptr<v::boundBox>>::iterator it);
    protected:
        PhysicScene();
    public:
        float getFrameTime() { return frameTime; };
        // deleting copy constructor
        PhysicScene(const PhysicScene& obj) = delete;
        ~PhysicScene() { m_scene->Shutdown(); instancePtr = nullptr; }

        std::shared_ptr<v::boundBox> getBbox(q3Vec3 positon, q3Vec3 size, bool isStatic,
                                            bool lockAxisX = false, bool lockAxisY = false, bool lockAxisZ = false);
        std::shared_ptr<v::boundBox> getBbox(glm::vec3 positon, glm::vec3 size, bool isStatic,
                                            bool lockAxisX = false, bool lockAxisY = false, bool lockAxisZ = false);
        void deleteBbox(std::shared_ptr<v::boundBox> box);
        void deleteBbox(const v::Object* box);
        void deleteBbox(const q3Body* body);
        void Dump(q3Body* body);
        void RayCast( q3QueryCallback *cb, q3RaycastData& rayCast ) const { m_scene->RayCast(cb, rayCast); }

        void ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix);
        void Draw();
        void Step() { m_scene->Step(); }
        void addWorldBorder(float Width, glm::vec3 position = glm::vec3(0.0f));
        static PhysicScene* getInstance()
        {
            if (instancePtr == nullptr)
            {
                instancePtr = new PhysicScene();
                return instancePtr;
            }
            else
                return instancePtr;
        }
    };

}; // namespace v

#endif // _PHYS_SCENE_H

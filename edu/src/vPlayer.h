#ifndef _V_PLAYER_H
#define _V_PLAYER_H

#include "vDynamicModel.h"
#include "movable.h"

namespace v
{
    class Player: public DynamicModel, public Movable
    {
    private:
        q3Vec3 prevVelocity;
        q3Vec3 forwardVector;
        bool onGround;
        bool jumpPressed;

        float m_speed;
        float m_jumpHeight;
    public:
        Player(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath);
        void Move() override;
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
        void setForward(glm::vec3 vec) { forwardVector = q3Vec3(vec.x, vec.y, vec.z); }
        void setForward(q3Vec3 vec) { forwardVector = vec; }
    };
}

#endif // _V_PLAYER_H

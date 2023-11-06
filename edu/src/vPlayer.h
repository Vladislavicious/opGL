#ifndef _V_PLAYER_H
#define _V_PLAYER_H

#include "vDynamicModel.h"
#include "cameraHandler.h"
#include "movable.h"
#include "vRaycast.h"

namespace v
{
    class Player: public DynamicModel, public Movable
    {
    private:

        enum class RayActions{
            Push, Delete, Dump
        };
        q3Vec3 prevVelocity;
        q3Vec3 forwardVector;
        bool onGround;
        bool jumpPressed;

        float m_speed;
        float m_jumpHeight;


        CameraHandler m_camHandler;
        Raycast m_ray;
        std::unique_ptr<Object> m_cross;
        void addBody();
    public:
        Player(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath);

        void Move() override;
        void Draw() override;
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
        void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

        void setForward(glm::vec3 vec) { forwardVector = q3Vec3(vec.x, vec.y, vec.z); }
        void setForward(q3Vec3 vec) { forwardVector = vec; }

        void ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix) override;

        void Ray(RayActions ra);
        void Update();
        bool isActive() { return m_camHandler.isActive(); }
        void ToggleCamera() { m_camHandler.ToggleCamera(); }
        glm::vec3 getCameraPosition() { return m_camHandler.getPosition(); }
        glm::vec3 getFront() { return m_camHandler.getFront(); }
        glm::mat4 getViewMatrix() { return m_camHandler.getViewMatrix(); }
    };
}

#endif // _V_PLAYER_H

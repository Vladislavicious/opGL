#include "vPlayer.h"

namespace v
{
    Player::Player(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath):
                DynamicModel(position, size, filePath, vsShaderPath, fsShaderPath), Movable(),
                forwardVector(q3Vec3(0.0f, 0.0f, 0.0f)), onGround(true), jumpPressed(false), m_speed(3.0f),
                m_jumpHeight(2.0f)
    {
    }

    void Player::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {

        Movable::key_callback(window, key, scancode, action, mods);
        if (onGround && key == GLFW_KEY_X)
        {
            jumpPressed = true;
        }
    }

    void Player::Move()
    {
        q3Vec3 velocity;
        q3Identity(velocity);
        auto vec = getVelocity();
        if (jumpPressed && onGround)
        {
            velocity += q3Vec3(0.0f, m_jumpHeight, 0.0f);
            jumpPressed = false;
            onGround = false;
        }
        if (!onGround && prevVelocity.y < -0.1f && vec.y >= -0.1f)
        {
            onGround = true;
        }
        prevVelocity = vec;
        forwardVector.y = 0.0f;

        if (direction[v::dir::Forward])
            velocity += q3Vec3(forwardVector);
        else if(direction[v::dir::Backward])
            velocity += q3Vec3(-forwardVector);
        if(direction[v::dir::Right])
            velocity += q3Cross(forwardVector, q3Vec3(0.0f, 1.0f, 0.0f));
        if(direction[v::dir::Left])
            velocity += q3Cross(-forwardVector, q3Vec3(0.0f, 1.0f, 0.0f));
        if (velocity.x || velocity.y || velocity.z)
        {
            velocity = q3Normalize(velocity) * m_speed;
            velocity.y += vec.y;
            applyVelocity(velocity);
        }
    }

}

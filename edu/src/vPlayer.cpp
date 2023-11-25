#include "vPlayer.h"
#include "pPhysicsScene.h"

namespace v
{
    Player::Player(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath):
                DynamicModel(position, size, filePath, vsShaderPath, fsShaderPath), Movable(),
                forwardVector(q3Vec3(0.0f, 0.0f, 0.0f)), onGround(true), jumpPressed(false), m_speed(3.0f),
                m_jumpHeight(2.0f),
                m_cross(new Object(glm::vec3(0.0f), glm::vec3(0.003f), "../edu/res/cube/cube.obj",
                        "../edu/res/BaseShader.vs", "../edu/res/BasicShader.fs"))
    {
    }

    void Player::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_Z && action == GLFW_PRESS && action != GLFW_REPEAT)
        {
            if (m_camHandler.attached)
                m_camHandler.unAttach();
            else
                m_camHandler.attachCamera(this, glm::vec3(0.0f, 1.5f, 0.0f));
            return;
        }

        if (key == GLFW_KEY_V)
            Ray(RayActions::Dump);
        if (!m_camHandler.attached)
        {
            m_camHandler.key_callback(window, key, scancode, action, mods);
            return;
        }

        Movable::key_callback(window, key, scancode, action, mods);
        if (key == GLFW_KEY_SPACE && onGround && action == GLFW_PRESS)
        {
            jumpPressed = true;
        }
    }

    void Player::mouse_callback(GLFWwindow *window, double xpos, double ypos)
    {
        m_camHandler.mouse_callback(window, xpos, ypos);
        if (m_camHandler.attached)
        {
            auto vec = m_camHandler.getFront();
            setForward(vec);
        }
    }

    void Player::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        {
            addBody();
        }
        if (m_camHandler.attached)
                return;
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {

            if (action == GLFW_PRESS)
                m_ray.Activate();
            if (action == GLFW_RELEASE)
                m_ray.DeActivate();
        }
        if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
        {
            Ray(RayActions::Delete);
        }
    }

    void Player::Ray(RayActions ra)
    {
        auto cp = getCameraPosition();
        auto dir = getFront();
        m_ray.Cast(  q3Vec3(cp.x, cp.y, cp.z), q3Vec3(dir.x, dir.y, dir.z) );
        auto scene = v::PhysicScene::getInstance();

        scene->RayCast( &m_ray, m_ray.data );

        if ( !m_ray.impactBody )
            return;

        switch (ra)
        {
            case RayActions::Push:
                m_ray.impactBody->SetToAwake();
                m_ray.impactBody->ApplyForceAtWorldPoint( m_ray.data.dir * 20.0f, m_ray.data.GetImpactPoint( ) );
                break;
            case RayActions::Delete:
                scene->deleteBbox(m_ray.impactBody);
                break;
            case RayActions::Dump:
                scene->Dump(m_ray.impactBody);
                break;
        }
    }

    void Player::ToDrawShader(glm::mat4 &viewMatrix, glm::mat4 &projMatrix)
    {
        Object::ToDrawShader(viewMatrix, projMatrix);
        m_cross->setPos(getCameraPosition() + getFront());
        m_cross->ToDrawShader(viewMatrix, projMatrix);
    }

    void Player::addBody()
    {
        auto scene = v::PhysicScene::getInstance();
        scene->getBbox(getCameraPosition() + getFront() * 3.0f, glm::vec3(1.0f), false);
    }

    void Player::Update()
    {
        m_camHandler.update();

        if (m_ray.active)
            Ray(RayActions::Push);
    }

    glm::mat4 Player::getProjectionMatrix()
    {
        if (m_camHandler.attached)
            return m_camHandler.getProjectionMatrix(0.01f + 0.9f, 70.0f);
        return m_camHandler.getProjectionMatrix(0.01f, 70.0f);
    }

    void Player::Draw()
    {
        DynamicModel::Draw();
        m_cross->Draw();
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

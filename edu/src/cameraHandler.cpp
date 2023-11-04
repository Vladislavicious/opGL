#include "cameraHandler.h"

CameraHandler::CameraHandler():
    m_camera(new myCamera()), m_obj(), attached(false)
{
}

void CameraHandler::attachCamera(std::shared_ptr<v::Object> obj, glm::vec3 offset)
{
    attachmentOffset = offset;
    prevPosition = m_camera->getPosition();
    attached = true;
    m_obj = std::weak_ptr<v::Object>(obj);
}

void CameraHandler::update()
{
    if (!m_obj.expired())
        m_camera->setPosition( m_obj.lock()->getPos() + attachmentOffset );
    else
        m_camera->updatePosition();
}

void CameraHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    m_camera->key_callback(window, key, scancode, action, mods);
}

void CameraHandler::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    m_camera->mouse_callback(window, xpos, ypos);
}

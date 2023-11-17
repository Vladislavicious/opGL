#include "cameraHandler.h"
extern int WinWidth;
extern int WinHeight;

CameraHandler::CameraHandler():
    m_camera(new myCamera()), m_obj(), attached(false),
    FOV(60.0f)
{
}

void CameraHandler::attachCamera(v::Object* obj, glm::vec3 offset)
{
    attachmentOffset = offset;
    prevPosition = m_camera->getPosition();
    attached = true;
    m_obj = obj;
}

void CameraHandler::update()
{
    if (m_obj != nullptr)
        m_camera->setPosition( m_obj->getPos() + attachmentOffset );
    else
        m_camera->updatePosition();
}

glm::mat4 CameraHandler::getProjectionMatrix(float near_z_bound, float far_z_bound)
{
    return glm::perspective(glm::radians(FOV), (float)WinWidth / (float)WinHeight, near_z_bound, far_z_bound);
}

void CameraHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    m_camera->key_callback(window, key, scancode, action, mods);
}

void CameraHandler::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    m_camera->mouse_callback(window, xpos, ypos);
}

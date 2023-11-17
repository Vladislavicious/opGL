#ifndef _CAMERA_HANDLER_H
#define _CAMERA_HANDLER_H

#include "myCamera.h"
#include "vObject.h"
#include <vector>
#include <memory>

class CameraHandler
{
private:
    std::unique_ptr<myCamera> m_camera;
    v::Object* m_obj;
    glm::vec3 prevPosition;
    glm::vec3 attachmentOffset;

    float FOV;
public:
    bool attached;
    bool isActive() { return m_camera->active; }
    glm::vec3 getPosition() { return m_camera->getPosition(); }
    glm::vec3 getFront() { return m_camera->getFront(); }
    glm::mat4 getViewMatrix() { return m_camera->getViewMatrix(); }

    CameraHandler();
    glm::mat4 getProjectionMatrix(float near_z_bound, float far_z_bound);
    void setInitialFront(glm::vec3 front) { m_camera->setInitialFront(front); }
    void ToggleCamera() { m_camera->toggleMouse(); }
    void attachCamera(v::Object* obj, glm::vec3 offset = glm::vec3(0.0f, 1.0f, 0.0f));
    void unAttach() { attached = false; m_obj = nullptr; m_camera->setPosition(prevPosition); }
    void update();

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};


#endif

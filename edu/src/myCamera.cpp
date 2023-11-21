#include "myCamera.h"
#include <iostream>

extern int WinWidth;
extern int WinHeight;
extern float deltaTime;

myCamera::myCamera():
    cameraPos(glm::vec3(0.0f))
{
    cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    currentSpeed= glm::vec3(0.0f, 0.0f,  0.0f);

    Stop();

    lastX = WinWidth / 2.0f;
    lastY = WinHeight / 2.0f;
    yaw = 90.0f;
    pitch = 0.0f;
    speed = 0.05f;
    firstMouse = true;
    active = false;
}

glm::mat4 myCamera::getViewMatrix()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void myCamera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Movable::key_callback(window, key, scancode, action, mods);

    Move();
}

void myCamera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!active )
        return;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void myCamera::toggleMouse()
{
    if ( active )
    {
        currentSpeed = glm::vec3(0.0f);
        for (int i = 0; i<4; i++)
            direction[i] = false;
        firstMouse = true;
    }
    active = !active;
}

void myCamera::Move()
{
    currentSpeed = glm::vec3(0.0f);
    if (direction[v::dir::Forward])
        currentSpeed += speed * cameraFront;
    else if(direction[v::dir::Backward])
        currentSpeed -= speed * cameraFront;
    if(direction[v::dir::Right])
        currentSpeed += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    else if(direction[v::dir::Left])
        currentSpeed -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
}

void myCamera::updatePosition()
{

    cameraPos += currentSpeed;
}

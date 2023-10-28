#include "myCamera.h"

extern int WinWidth;
extern int WinHeight;
extern float deltaTime;


myCamera::myCamera()
{
    cameraPos   = glm::vec3(0.0f, 0.0f,  0.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    lastX = WinWidth / 2.0f;
    lastY = WinHeight / 2.0f;
    yaw = 90.0f;
    pitch = 0.0f;
    speed = 15.5f;
    firstMouse = true;
    active = false;
}

glm::mat4 myCamera::getViewMatrix()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void myCamera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (!active && key != GLFW_KEY_SPACE)
        return;
    float cameraSpeed = speed * deltaTime; //deltaTime - global variable from renderer.h
    switch (key)
    {
    case GLFW_KEY_W:
        if ( action == GLFW_PRESS || action == GLFW_REPEAT )
        {
            cameraPos += cameraSpeed * cameraFront;
            break;
        }
    case GLFW_KEY_S:
        if ( action == GLFW_PRESS || action == GLFW_REPEAT )
        {
            cameraPos -= cameraSpeed * cameraFront;
            break;
        }
    case GLFW_KEY_D:
        if ( action == GLFW_PRESS || action == GLFW_REPEAT )
        {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            break;
        }
    case GLFW_KEY_A:
        if ( action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            break;
        }
    case GLFW_KEY_SPACE:
        if ( action == GLFW_PRESS && action != GLFW_REPEAT)
        {
            myCamera::toggleMouse(window);
            break;
        }
    default:
        break;
    }

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

void myCamera::toggleMouse(GLFWwindow *window)
{
    if ( active )
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstMouse = true;
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    active = !active;
}

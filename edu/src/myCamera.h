#ifndef MY_CAMERA_H_
#define MY_CAMERA_H_

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW

enum dir{
    Forward = 0,
    Backward = 1,
    Left = 2,
    Right = 3
};

class myCamera
{
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    glm::vec3 currentSpeed;

    float yaw; // up-down
    float pitch; // left-right
    float lastX;
    float lastY;
    float speed;
    bool firstMouse;

    bool direction[4];
    void MoveCamera();
public:
    bool active;
    myCamera();
    void toggleMouse(GLFWwindow* window);
    void setPosition(glm::vec3 position) { cameraPos = position; }
    glm::vec3 getPosition() { return cameraPos; }
    glm::vec3 getFront() { return cameraFront; }
    void setInitialFront(glm::vec3 front) { cameraFront = front; }
    glm::mat4 getViewMatrix();
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};
#endif // MY_CAMERA_H_

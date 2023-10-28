#ifndef MY_CAMERA_H_
#define MY_CAMERA_H_

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW

class myCamera
{
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float yaw; // up-down
    float pitch; // left-right
    float lastX;
    float lastY;
    float speed;
    bool firstMouse;
public:
    bool active;
    myCamera();
    void toggleMouse(GLFWwindow* window);
    void initialize(GLFWwindow *window);
    glm::vec3 getPosition() { return cameraPos; }
    glm::vec3 getFront() { return cameraFront; }
    glm::mat4 getViewMatrix();
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};
#endif // MY_CAMERA_H_

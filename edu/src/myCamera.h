#ifndef MY_CAMERA_H_
#define MY_CAMERA_H_

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW

class myCamera
{
private:
    static glm::vec3 cameraPos;
    static glm::vec3 cameraFront;
    static glm::vec3 cameraUp;

    static float yaw; // up-down
    static float pitch; // left-right
    static float lastX;
    static float lastY;
    static float speed;
    static bool firstMouse;
public:
    static bool active;
    static void toggleMouse(GLFWwindow* window);
    static void initialize(GLFWwindow *window);
    static glm::vec3 getPosition() { return cameraPos; }
    static glm::vec3 getFront() { return cameraFront; }
    static glm::mat4 getViewMatrix();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};
#endif // MY_CAMERA_H_

#ifndef _MOVABLE_H
#define _MOVABLE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW
namespace v
{
    enum dir{
        Forward = 0,
        Backward = 1,
        Left = 2,
        Right = 3
    };

    class Movable
    {
    protected:
        bool direction[4];
        virtual void Stop() { for (int i = 0; i<4; i++) direction[i] = false; }
    public:
        Movable() { Stop(); }
        virtual void Move() {}
        virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_W)
            {
                if ( action == GLFW_PRESS)
                    direction[dir::Forward] = true;
                else if ( action == GLFW_RELEASE )
                    direction[dir::Forward] = false;
            }
            else if (key == GLFW_KEY_S)
            {
                if ( action == GLFW_PRESS )
                    direction[dir::Backward] = true;
                else if ( action == GLFW_RELEASE )
                    direction[dir::Backward] = false;
            }
            if (key == GLFW_KEY_D)
            {
                if ( action == GLFW_PRESS )
                    direction[dir::Right] = true;
                else if ( action == GLFW_RELEASE )
                    direction[dir::Right] = false;
            }
            else if (key == GLFW_KEY_A)
            {
                if ( action == GLFW_PRESS )
                    direction[dir::Left] = true;
                else if ( action == GLFW_RELEASE )
                    direction[dir::Left] = false;
            }
        }

    };
};
#endif // _MOVABLE_H

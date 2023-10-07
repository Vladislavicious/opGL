#include "Renderer.h"

#include <stdio.h>
#include <stdlib.h>
#include "windows.h"

GLfloat* get_random_points(int number_of_colors)
{
    srand(1);
    GLfloat* arr = new GLfloat[number_of_colors];
    for (int j=0;j<number_of_colors/3;j++)
    {
        if (j % 2 ==0)
        {
            for(int i = j * 3; i < j * 3 + 3; i++)
            {
                arr[i] = ((float)rand()) / (RAND_MAX / 2) - 1;
            }
        }
        else
        {
            for(int i = j * 3; i < j * 3 + 3; i++)
            {
                arr[i] = ((float)rand()) / RAND_MAX;
            }
        }
    }

    return arr;
}

int WinWidth= 640;
int WinHeight= 480;
void glfw_window_size_callback (GLFWwindow* window, int width, int height);

int main()
{
    //                                        Инициализация
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    GLFWmonitor* mon = glfwGetPrimaryMonitor ();
    const GLFWvidmode* vmode = glfwGetVideoMode (mon);
    GLFWwindow* window = glfwCreateWindow (640, 480, "Figure", NULL, NULL);
    glfwSetWindowSizeCallback (window, glfw_window_size_callback);

    if (!window)
    {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);                     //Созданное окно выбирается как текущее

    glewExperimental = GL_TRUE;                         // Подключение новейшей из доступных версий OpenGL

    glewInit();                                         //Включение GLEW
    glEnable(GL_DEPTH_TEST);                            // Включение буфера глубины
    glDepthFunc(GL_LESS);                               // А вот тут можно управлять его работой. Сейчас установлен режим по умолчанию
    //                                         Определение координат

    GLfloat points[] = {
        -0.5, 0.5, 0.8, 0.9, 0.3, // 0
        -0.2, 0.7, 0.2, 1.0, 0.3, // 1
        0.0, 0.3, 0.1, 0.8, 0.0, // 2
        0.4, 0.7, 0.1, 0.3, 0.8, // 3
        0.3, 0.0, 0.6, 0.4, 0.1, // 4
        0.0, -0.3, 0.6, 0.5, 1.0, // 5
        -0.3, -0.2, 0.7, 0.1, 0.4, // 6
        -0.7, 0.2, 0.5, 0.6, 0.7 // 7
    };

    int coord_number = sizeof(points) / sizeof(GLfloat);

    auto points_buffer = VertexBuffer(points, coord_number * sizeof(GLfloat));

    VertexBufferLayout vbLayout;
    vbLayout.Push<float>(2); // 2 координаты
    vbLayout.Push<float>(3); // 3 цвета

    VertexArray vertexArray;
    vertexArray.AddBuffer(points_buffer, vbLayout);


    unsigned int vertexIndices[] = {
            0, 1, 2,
            1, 2, 3,
            2, 3, 4,
            4, 2, 5,

            6, 5, 2,
            7, 6, 0,
            0, 2, 6,
            4, 5, 6,

            0, 2, 7,
            0, 1, 3,
            3, 4, 1,
            3, 4, 5,

            0, 7, 1,
            5, 0, 7,
            7, 6, 3,
            0, 1, 5
    };

    IndexBuffer indexBufferObject(vertexIndices, sizeof(vertexIndices) / sizeof(unsigned int));

    auto shader = Shader(PROJECT_DIR "res\\BasicShader.shader");

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        renderer.Draw(vertexArray, indexBufferObject, shader);
        glfwPollEvents();                               //Обработка очереди событий
        glfwSwapBuffers(window);                        //Использование двойной буферизации
        if (GLFW_PRESS == glfwGetKey (window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose (window, 1);
        }
        glViewport(0, 0, WinWidth, WinHeight);
    }
    glfwTerminate();
    return 0;
}

void glfw_window_size_callback (GLFWwindow* window, int width, int height)
{
    WinWidth = width;
    WinHeight = height;
}

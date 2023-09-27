#include "Renderer.h"

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


    GLfloat old_points[] = {
         -0.7f,  -0.5f, 1.0f, 0.0f, 0.0f, // Левый нижний
         -0.4f,   0.7f, 0.0f, 1.0f, 0.0f, // Левый верхний
          0.4f,   0.8f, 0.0f, 1.0f, 0.0f,
          0.3f,   0.1f, 0.0f, 1.0f, 0.0f,
          0.8f,   0.2f, 0.0f, 0.0f, 1.0f, // Правый синий сверху
          0.8f,  -0.2f, 0.0f, 0.0f, 1.0f, // правый синий снизу
          0.3f,  -0.2f, 1.0f, 0.0f, 0.0f,
          0.3f,  -0.8f, 1.0f, 0.0f, 0.0f,
         -0.3f,  -0.2f, 0.0f, 0.0f, 1.0f,
    };

    GLfloat points[] = {
         -0.7f,  -0.5f, 1.0f, 0.0f, 0.0f, //1
         -0.4f,   0.7f, 0.0f, 1.0f, 0.0f, //2
         -0.3f,  -0.2f, 0.0f, 0.0f, 1.0f, //9
          0.4f,   0.8f, 0.0f, 1.0f, 0.0f, //3
          0.3f,   0.1f, 0.0f, 1.0f, 0.0f, //4
          0.3f,   0.1f, 0.0f, 1.0f, 0.0f, //4
          0.3f,  -0.2f, 1.0f, 0.0f, 0.0f, //7
          0.8f,   0.2f, 0.0f, 0.0f, 1.0f, //5
          0.8f,  -0.2f, 0.0f, 0.0f, 1.0f, //6
          0.3f,   0.1f, 0.0f, 1.0f, 0.0f, //4
          0.3f,   0.1f, 0.0f, 1.0f, 0.0f, //4
          0.3f,  -0.8f, 1.0f, 0.0f, 0.0f, //8
         -0.3f,  -0.2f, 0.0f, 0.0f, 1.0f, //9
    };




    int coord_number = sizeof(points) / sizeof(GLfloat);

    auto points_buffer = VertexBuffer(points, coord_number * sizeof(GLfloat));

    VertexArray vertexArray;

    VertexBufferLayout vbLayout;
    vbLayout.Push<float>(2);
    vbLayout.Push<float>(3);

    vertexArray.AddBuffer(points_buffer, vbLayout);

    std::vector<std::string> attribLocations;
    attribLocations.push_back("vector_position");
    attribLocations.push_back("vector_color");

    Shader shader = Shader("../BasicShader.shader", attribLocations);

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        renderer.Draw(vertexArray, shader, coord_number / 5);
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

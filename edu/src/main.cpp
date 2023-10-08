#include "Renderer.h"


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

    VertexBufferLayout vbLayout;
    vbLayout.Push<float>(2); // 2 координаты
    vbLayout.Push<float>(3); // 3 цвета

    GLfloat line[] = {
        -0.5f, -0.5f, 0.5f, 0.1f, 0.3f,
         0.5f,  0.5f, 0.4f, 0.3f, 0.2f,
    };

    auto lineBuffer = VertexBuffer(line, sizeof(line));

    VertexArray lineVertexArray;
    lineVertexArray.AddBuffer(lineBuffer, vbLayout);
    unsigned int lineIndices[] = {
        0, 1
    };

    IndexBuffer lineIndexBuffer(lineIndices, sizeof(lineIndices) / sizeof(unsigned int));
    lineVertexArray.UnBind();
    lineBuffer.UnBind();
    lineIndexBuffer.UnBind();


    glm::mat4 none = glm::mat4(1.0f); // Единичная матрица
    glm::mat4 lineRotation = glm::rotate(none, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 secondLineRotation = glm::rotate(none, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));


    auto shader = Shader(PROJECT_DIR "res\\BasicShader.shader");
    shader.Bind();
    shader.SetUniformMat4f("u_MVP", none);

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();


        shader.Bind();
        shader.SetUniformMat4f("u_MVP", none);
        renderer.Draw(lineVertexArray, lineIndexBuffer, shader, GL_LINES);
        shader.SetUniformMat4f("u_MVP", lineRotation);
        renderer.Draw(lineVertexArray, lineIndexBuffer, shader, GL_LINES);
        shader.SetUniformMat4f("u_MVP", secondLineRotation);
        renderer.Draw(lineVertexArray, lineIndexBuffer, shader, GL_LINES);


        glfwPollEvents();                               //Обработка очереди событий
        glfwSwapBuffers(window);                        //Использование двойной буферизации
        if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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

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
    GLFWwindow* window = glfwCreateWindow (640, 480, "Figures", NULL, NULL);
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

    GLfloat triangle[] = {
        -0.5f, 0.3f, 0.1f, 0.8f, 0.0f,
        -0.4f, 0.7f, 0.1f, 0.3f, 0.8f,
        -0.1f, 0.0f, 0.6f, 0.4f, 0.1f
    };

    auto triangleBuffer = VertexBuffer(triangle, sizeof(triangle));

    VertexArray triangleVertexArray;
    triangleVertexArray.AddBuffer(triangleBuffer, vbLayout);
    unsigned int triangleIndices[] = {
        0, 1, 2
    };

    IndexBuffer trinagleIndexBuffer(triangleIndices, sizeof(triangleIndices) / sizeof(unsigned int));
    triangleVertexArray.UnBind();
    triangleBuffer.UnBind();
    trinagleIndexBuffer.UnBind();

    GLfloat line[] = {
        0.1f, 0.7f, 0.5f, 0.1f, 0.3f,
        0.7f, 0.8f, 0.4f, 0.3f, 0.2f,
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

    GLfloat rectangle[] = {
        0.9f, -0.8f, 0.1f, 0.5f, 0.7f,
        0.9f, 0.3f, 0.2f, 0.1f, 0.8f,
        0.0f, 0.3f, 0.9f, 0.5f, 0.3f,
        0.0f, -0.8f, 0.1f, 0.1f, 0.3f,
    };

    auto rectangleBuffer = VertexBuffer(rectangle, sizeof(rectangle));

    VertexArray rectangleVertexArray;
    rectangleVertexArray.AddBuffer(rectangleBuffer, vbLayout);
    unsigned int rectangleIndices[] = {
        0, 1, 3,
        1, 2, 3
    };

    IndexBuffer rectangleIndexBuffer(rectangleIndices, sizeof(rectangleIndices) / sizeof(unsigned int));
    rectangleVertexArray.UnBind();
    rectangleBuffer.UnBind();
    rectangleIndexBuffer.UnBind();


    glm::mat4 none = glm::mat4(1.0f); // Единичная матрица
    glm::vec3 kxky = { 1.2, 1.5, 1.0 };
    glm::vec3 shift = { 0.3, 0.15 , 0 };
    glm::mat4 triangleScale = glm::scale(none, kxky);
    triangleScale = glm::translate(triangleScale, shift);

    glm::mat4 lineRotation = glm::rotate(none, glm::radians(40.0f), glm::vec3(0.0, 0.0, 1.0));

    glm::mat4 rectRotation = glm::rotate(none, glm::radians(-25.0f), glm::vec3(-3.0, 8.0, 1.0));

    auto shader = Shader(PROJECT_DIR "res\\BasicShader.shader");
    shader.Bind();

    glm::mat4* triangleTransform = &none;
    glm::mat4* lineTransform = &none;
    glm::mat4* rectangleTransform = &none;

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        shader.Bind();
        shader.SetUniformMat4f("u_MVP", *triangleTransform);
        renderer.Draw(triangleVertexArray, trinagleIndexBuffer, shader, GL_TRIANGLES);

        shader.SetUniformMat4f("u_MVP", *lineTransform);
        renderer.Draw(lineVertexArray, lineIndexBuffer, shader, GL_LINES);

        shader.SetUniformMat4f("u_MVP", *rectangleTransform);
        renderer.Draw(rectangleVertexArray, rectangleIndexBuffer, shader, GL_TRIANGLES);


        glfwPollEvents();                               //Обработка очереди событий
        glfwSwapBuffers(window);                        //Использование двойной буферизации
        if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose (window, 1);
        }

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            if (triangleTransform == &none)
                triangleTransform = &triangleScale;
            else
                triangleTransform = &none;
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            if (lineTransform == &none)
                lineTransform = &lineRotation;
            else
                lineTransform = &none;
        }

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        {
            if (rectangleTransform == &none)
                rectangleTransform = &rectRotation;
            else
                rectangleTransform = &none;
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

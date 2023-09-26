#include "Renderer.h"

GLfloat* get_random_points(int number_of_points)
{
    GLfloat* arr = new GLfloat[number_of_points];
    for (int i=0;i<number_of_points;i++)
    {
        arr[i] = ((float)rand()) / (RAND_MAX / 2) - 1;
    }
    return arr;
}

GLfloat* get_random_colors(int number_of_colors)
{
    GLfloat* arr = new GLfloat[number_of_colors];
    for (int i=0;i<number_of_colors;i++)
    {
        arr[i] = ((float)rand()) / RAND_MAX;
    }
    return arr;
}

GLuint get_vao(GLfloat points[], GLfloat colors[], int coord_number)
{
    auto points_buffer = VertexBuffer(points, coord_number * sizeof(GLfloat));
    auto colors_buffer = VertexBuffer(colors, coord_number * sizeof(GLfloat));

    GLuint vao = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    points_buffer.Bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    colors_buffer.Bind();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    return vao;
}

int main()
{
    //                                        Инициализация
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Triangle", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);                     //Созданное окно выбирается как текущее

    glewExperimental = GL_TRUE;                         // Подключение новейшей из доступных версий OpenGL

    glewInit();                                         //Включение GLEW
    const GLubyte* renderer = glGetString(GL_RENDERER); // информация о графической карте
    const GLubyte* version = glGetString(GL_VERSION);   // информация о версии OpenGL
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
    glEnable(GL_DEPTH_TEST);                            // Включение буфера глубины
    glDepthFunc(GL_LESS);                               // А вот тут можно управлять его работой. Сейчас установлен режим по умолчанию
    //                                         Определение координат
    int coord_number = 9; // Количество координат вершин

    GLuint vao = get_vao(get_random_points(coord_number), get_random_colors(coord_number), coord_number);
    GLuint vao1 = get_vao(get_random_points(coord_number), get_random_colors(coord_number), coord_number);
    GLuint vao2 = get_vao(get_random_points(coord_number), get_random_colors(coord_number), coord_number);

    std::vector<std::string> attribLocations;
    attribLocations.push_back("vector_position");
    attribLocations.push_back("vector_color");

    Shader shader = Shader("BasicShader.shader", attribLocations);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        glBindVertexArray(vao);                         //Подключается массив вершин
        glDrawArrays(GL_TRIANGLES, 0, coord_number / 3);               //Из массива рисуются три элемента начиная с элемента с индексом 0

        glBindVertexArray(vao1);
        glDrawArrays(GL_TRIANGLES, 0, coord_number / 3);

        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, coord_number / 3);
        glfwPollEvents();                               //Обработка очереди событий
        glfwSwapBuffers(window);                        //Использование двойной буферизации
    }
    glfwTerminate();
    return 0;
}

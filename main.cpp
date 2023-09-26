#include <GL/glew.h> // подключение GLEW
#include <GLFW/glfw3.h> // подключение GLFW
#include <stdio.h> //Для простого консольного вывода ошибок
#include <glm/glm.hpp>
#include <iostream>

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
    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, coord_number * sizeof(GLfloat), points, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, coord_number * sizeof(GLfloat), colors, GL_STATIC_DRAW);

    GLuint vao = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
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

    GLfloat points[coord_number] =
    {
        -0.5f,  -0.5f,  0.0f,
         0.0f,   0.5f,  0.0f,
         0.5f,  -0.5f,  0.0f,
    };

    GLfloat colors[coord_number] =
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    GLfloat points1[coord_number] =
    {
        -0.8f,  0.8f,  1.0f,
         0.0f,   0.0f,  0.0f,
         0.1f,  -0.2f,  0.0f,
    };

    GLfloat colors1[coord_number] =
    {
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
    };

    GLuint vao = get_vao(get_random_points(coord_number), get_random_colors(coord_number), coord_number);
    GLuint vao1 = get_vao(get_random_points(coord_number), get_random_colors(coord_number), coord_number);
    GLuint vao2 = get_vao(get_random_points(coord_number), get_random_colors(coord_number), coord_number);

    //                                              Шейдеры
    const char* vertex_shader_text =
    "#version 400\n"
    "layout (location = 0) in vec3 vector_position;"                                       //Входные данные. В данном случае это координаты одной точки
    "layout (location = 1) in vec3 vector_color;"
    "out vec3 colour;"

    "void main() {"                                     //Основная функция
    " gl_Position = vec4(vector_position, 1.0);"                     //В данном случае простое преобразование без вычисления сложной проекции
    " colour = vector_color;"
    "}";

    //Фрагмент - это по сути один пиксель на экране
    const char* fragment_shader_text =                       //Фрагментный шейдер отвечает за окрашивание каждого фрагмента
    "#version 400\n"                                    //Данный шейдер должен возвращать цвет пикселя
    "in vec3 colour;"
    "out vec4 frag_color;"                             //Цвет из 4-х координат - RGBA

    "void main() {"
    " frag_color = vec4(colour, 1.0);"
    "}";
    //                                          Загрузка шейдеров
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);


    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, vertex_shader);
    glAttachShader(shader_programme, fragment_shader);
    glBindAttribLocation(shader_programme, 0, "vector_position");
    glBindAttribLocation(shader_programme, 1, "vector_color");
    glLinkProgram(shader_programme);                   //Программа компонуется
    //                                          Вывод на экран

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_programme);                 //Подключается шейдерная программа
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

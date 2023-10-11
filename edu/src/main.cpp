#include "Renderer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
    GLFWwindow* window = glfwCreateWindow (WinWidth, WinHeight, "Figure", NULL, NULL);
    glfwSetWindowSizeCallback (window, glfw_window_size_callback);

    if (!window)
    {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);                     //Созданное окно выбирается как текущее
    glfwSwapInterval(1);


    glewExperimental = GL_TRUE;                         // Подключение новейшей из доступных версий OpenGL
    glewInit();                                         //Включение GLEW
    glEnable(GL_DEPTH_TEST);                            // Включение буфера глубины
    glDepthFunc(GL_LESS);                               // А вот тут можно управлять его работой. Сейчас установлен режим по умолчанию
    //                                         Определение координат
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    VertexBufferLayout vbLayout;
    vbLayout.Push<float>(2); // 2 координаты
    vbLayout.Push<float>(3); // 3 цвета

    GLfloat square[] = {
        -0.7f,   -0.7f, 0.5f, 0.1f, 0.5f,
        -0.7f,    0.7f, 0.5f, 0.4f, 0.3f,
         0.7f,    0.7f, 0.1f, 0.3f, 0.3f,
         0.7f,   -0.7f, 0.2f, 0.1f, 0.3f,
    };

    auto squareBuffer = VertexBuffer(square, sizeof(square));

    VertexArray squareVertexArray;
    squareVertexArray.AddBuffer(squareBuffer, vbLayout);
    unsigned int squareIndices[] = {
        0, 1, 2,
        2, 3, 0
    };

    IndexBuffer squareIndexBuffer(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));
    squareVertexArray.UnBind();
    squareBuffer.UnBind();
    squareIndexBuffer.UnBind();


    glm::mat4 unit = glm::mat4(1.0f); // Единичная матрица
    
    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(unit, glm::vec3(0.3f, -0.4f, 0.0f)); 
    glm::mat4 model = glm::translate(unit, glm::vec3(0.1f, 0.5f, 0.0f)); 

    glm::mat4 mvp = proj * view * model;

    auto shader = Shader(PROJECT_DIR "res\\BasicShader.shader");
    
    glm::vec3 translation(0.0f, 0.5f, 0.0f);

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        model = glm::translate(unit, translation);
        mvp = proj * view * model;

        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(squareVertexArray, squareIndexBuffer, shader, GL_TRIANGLES);

        glfwPollEvents();                               //Обработка очереди событий

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        ImGui::Begin("Debug properties");                          // Create a window called "Hello, world!" and append into it.


        ImGui::SliderFloat2("model position", &translation.x, -1.0f, 1.0f);  

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);                        //Использование двойной буферизации
        if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose (window, 1);
        }

        glViewport(0, 0, WinWidth, WinHeight);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void glfw_window_size_callback (GLFWwindow* window, int width, int height)
{
    WinWidth = width;
    WinHeight = height;
}

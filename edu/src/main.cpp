#include "Renderer.h"

#include "TestClearColor.h"
#include "TestMovingSquare.h"
#include "TestCube.h"
#include "testpr4_1.h"
#include "testpr4_2.h"

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


    /* Initialize GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "glad initialization went wrong!" << std::endl;
        return -1;
    }

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

    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestMovingSquare>("Moving Square");
    testMenu->RegisterTest<test::TestCube>("Rotating Cube");
    testMenu->RegisterTest<test::TestPR4_1>("PR4 task 1");
    testMenu->RegisterTest<test::TestPR4_2>("PR4 task 2");

    currentTest = new test::TestPR4_2();

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();


        glfwPollEvents();                               //Обработка очереди событий


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest != nullptr)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }

            currentTest->OnImGuiRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);                        //Использование двойной буферизации
        if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose (window, 1);
        }

        glViewport(0, 0, WinWidth, WinHeight);
    }

    if (currentTest != testMenu)
        delete testMenu;
    delete currentTest;

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

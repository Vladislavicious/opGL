#include "TestModel.h"
#include "loader.h"

namespace test {

	TestModel::TestModel()
	{

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        VertexBufferLayout vbLayout;
        vbLayout.Push<float>(3); // 3 координаты
        vbLayout.Push<float>(3); // 3 нормали
        vbLayout.Push<float>(2); // 2 текстурных координаты

        GLfloat cube[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };
        auto temp = getVertices(cube, 36);
        unsigned int cubeIndices[] = {
            0, 1, 2, 3, 4, 5,
            6, 7, 8, 9, 10, 11,
            12, 13, 14, 15, 16, 17,
            18, 19, 20, 21, 22, 23,
            24, 25, 26, 27, 28, 29,
            30, 31, 32, 33, 34, 35
        };
        std::vector<unsigned int> indices;
        indices.reserve(sizeof(cubeIndices) / sizeof(unsigned int));
        for (int i = 0; i < sizeof(cubeIndices) / sizeof(unsigned int); i++)
            indices.push_back(cubeIndices[i]);

        auto lightBuffer = VertexBuffer(cube, sizeof(cube));

        m_lightVertexArray = new VertexArray();
        m_lightVertexArray->AddBuffer(lightBuffer, vbLayout);

        m_lightIndexBuffer = new IndexBuffer(cubeIndices, sizeof(cubeIndices) / sizeof(unsigned int));
        m_lightVertexArray->UnBind();
        lightBuffer.UnBind();
        m_lightIndexBuffer->UnBind();

        z_ortho[0] = 0.01f;
        z_ortho[1] = 20.0f;

        m_camera = std::make_unique<CameraHandler>();
        m_camera->setInitialFront(glm::vec3(0.0f, 0.0f, -1.0f));

        m_proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, z_ortho[0], z_ortho[1]);

        m_lightPos = glm::vec3(-0.8f, -0.8f, 0.4f);
        m_lightModel = glm::translate(glm::mat4(1.0f), m_lightPos);
        m_lightModel = glm::scale(m_lightModel, glm::vec3(0.4f));
        m_pointLightColor = glm::vec3(1.0f, 0.0f, 0.0f);
        m_spotLightRadius = 12.0f;
        m_dirLightPower = glm::vec3(0.05f, 0.05f, 0.05f);

        m_modelShader = new Shader("../edu/res/meshShader.vs", "../edu/res/meshShader.fs");

        m_lightShader = new Shader("../edu/res/lightShader.vs", "../edu/res/lightShader.fs");


        m_backpack = new myModel("../edu/res/backpack/backpack.obj");

        float a = glfwGetTime();
        m_renderer = Renderer::getInstance();
        v::Loader::processLoadQueue();
        std::cout << "Time: " << glfwGetTime() - a << std::endl;

	}

	TestModel::~TestModel()
	{
        glDisable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        delete m_modelShader;

        delete m_backpack;

        delete m_lightIndexBuffer;
        delete m_lightShader;
        delete m_lightVertexArray;
        delete m_renderer;
	}

	void TestModel::OnUpdate(float deltaTime)
	{

        m_renderer->Clear();
        m_camera->update();
	}

	void TestModel::OnRender()
	{
        m_proj = getProjectionMatrix(z_ortho[0], z_ortho[1]);
        auto view = m_camera->getViewMatrix();
        m_lightShader->Bind();
        m_lightShader->SetUniformMat4f("model", m_lightModel);
        m_lightShader->SetUniformMat4f("view", view);
        m_lightShader->SetUniformMat4f("projection", m_proj);
        m_lightShader->SetUniform3f("colour", m_pointLightColor);

        m_modelShader->Bind();
        auto modelPlace = glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f, 1.0f, 0.0f));
        m_modelShader->SetUniformMat4f("model", modelPlace);
        m_modelShader->SetUniformMat4f("view", view);
        m_modelShader->SetUniformMat4f("projection", m_proj);
        m_modelShader->SetUniform1i("pointLightsNumber", 1);
        m_modelShader->SetUniform3f("pointLights[0].position",  m_lightPos);
        m_modelShader->SetUniform3f("pointLights[0].ambient",  0.3f, 0.3f, 0.3f);
        m_modelShader->SetUniform3f("pointLights[0].diffuse",  m_pointLightColor);
        m_modelShader->SetUniform3f("pointLights[0].specular",  1.0f, 1.0f, 1.0f);
        m_modelShader->SetUniform1f("pointLights[0].constant",  1.0f);
        m_modelShader->SetUniform1f("pointLights[0].linear",    0.09f);
        m_modelShader->SetUniform1f("pointLights[0].quadratic", 0.032f);
        m_modelShader->SetUniform3f("viewPos",  m_camera->getPosition());
        m_modelShader->SetUniform1f("material.shininess", 32.0f);

        if ( isDirLightOn )
        {
            m_modelShader->SetUniform3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
            m_modelShader->SetUniform3f("dirLight.ambient", m_dirLightPower);
            m_modelShader->SetUniform3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
            m_modelShader->SetUniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
        }
        else
            m_modelShader->SetUniform3f("dirLight.ambient", 0.0f, 0.0f, 0.0f);
        if ( isSpotLightOn )
        {
            m_modelShader->SetUniform3f("spotLight.position", m_camera->getPosition());
            m_modelShader->SetUniform3f("spotLight.direction", m_camera->getFront());
            m_modelShader->SetUniform3f("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            m_modelShader->SetUniform3f("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            m_modelShader->SetUniform3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
            m_modelShader->SetUniform1f("spotLight.constant", 1.0f);
            m_modelShader->SetUniform1f("spotLight.linear", 0.09f);
            m_modelShader->SetUniform1f("spotLight.quadratic", 0.032f);
            m_modelShader->SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(m_spotLightRadius)));
            m_modelShader->SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(m_spotLightRadius + 3.0f)));
        }
        else
            m_modelShader->SetUniform3f("spotLight.diffuse", 0.0f, 0.0f, 0.0f);

        m_renderer = Renderer::getInstance();
        m_backpack->Draw(*m_modelShader);

        m_renderer->Draw(*m_lightVertexArray, *m_lightIndexBuffer, *m_lightShader);
	}

	void TestModel::OnImGuiRender()
	{
        ImGui::SetWindowCollapsed(isRunning());
        if (isRunning())
            return;

        if ( ImGui::Button("DirLight"))
            isDirLightOn = !isDirLightOn;

        if ( ImGui::Button("SpotLight"))
            isSpotLightOn = !isSpotLightOn;

        ImGui::SliderFloat3("light colour", &m_pointLightColor.x, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat3("directional light", &m_dirLightPower.x, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat("spotLight radius", &m_spotLightRadius, 10.0f, 50.0f, "%.2f");

        auto& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}

    glm::mat4 TestModel::getProjectionMatrix(float near_z_bound, float far_z_bound)
    {
        return glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, near_z_bound, far_z_bound);
    }

    void TestModel::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            if (isRunning())
            {
                Toggle();
                m_camera->ToggleCamera();
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            else
            {
                glfwSetWindowShouldClose (window, 1);
            }
            return;
        }
        if (key == GLFW_KEY_SPACE)
        {
            if (!isRunning())
            {
                Toggle();
                m_camera->ToggleCamera();
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                return;
            }
        }
        if (!isRunning())
            return;
        m_camera->key_callback(window, key, scancode, action, mods);
    }

    void TestModel::mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (!isRunning())
            return;
        m_camera->mouse_callback(window, xpos, ypos);
    }
}

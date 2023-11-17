#include "TestLighting.h"

namespace test {

	TestLighting::TestLighting()
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

        m_cubePositions[0] = glm::vec3( 0.0f,  0.0f,  0.0f);
        m_cubePositions[1] = glm::vec3( 2.0f,  5.0f, 15.0f);
        m_cubePositions[2] = glm::vec3(-1.5f, -2.2f, 2.5f);
        m_cubePositions[3] = glm::vec3(-3.8f, -2.0f, 12.3f);
        m_cubePositions[4] = glm::vec3( 2.4f, -0.4f, 3.5f);
        m_cubePositions[5] = glm::vec3(-1.7f,  3.0f, 7.5f);
        m_cubePositions[6] = glm::vec3( 1.3f, -2.0f, 2.5f);
        m_cubePositions[7] = glm::vec3( 1.5f,  2.0f, 2.5f);
        m_cubePositions[8] = glm::vec3( 1.5f,  0.2f, 1.5f);
        m_cubePositions[9] = glm::vec3(-1.3f,  1.0f, 1.5f);

        auto squareBuffer = VertexBuffer(cube, sizeof(cube));

        m_cubeVertexArray = new VertexArray();
        m_cubeVertexArray->AddBuffer(squareBuffer, vbLayout);
        unsigned int cubeIndices[] = {
            0, 1, 2, 3, 4, 5,
            6, 7, 8, 9, 10, 11,
            12, 13, 14, 15, 16, 17,
            18, 19, 20, 21, 22, 23,
            24, 25, 26, 27, 28, 29,
            30, 31, 32, 33, 34, 35
        };

        m_cubeIndexBuffer = new IndexBuffer(cubeIndices, sizeof(cubeIndices) / sizeof(unsigned int));
        m_cubeVertexArray->UnBind();
        squareBuffer.UnBind();
        m_cubeIndexBuffer->UnBind();

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

        m_proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, z_ortho[0], z_ortho[1]);
        m_cubeModel = glm::mat4(1.0f);
        m_cubeTexture = new Texture("../edu/res/cont.png");
        m_cubeSpecTexture = new Texture("../edu/res/spec.png");

        m_lightPos = glm::vec3(-0.8f, -0.8f, 0.4f);
        m_lightModel = glm::translate(glm::mat4(1.0f), m_lightPos);
        m_lightModel = glm::scale(m_lightModel, glm::vec3(0.4f));
        m_pointLightColor = glm::vec3(1.0f, 0.0f, 0.0f);
        m_spotLightRadius = 12.0f;
        m_dirLightPower = glm::vec3(0.05f, 0.05f, 0.05f);

        m_cubeShader = new Shader("../edu/res/cubeShader.vs", "../edu/res/cubeShader.fs");

        m_lightShader = new Shader("../edu/res/lightShader.vs", "../edu/res/lightShader.fs");

        m_renderer = Renderer::getInstance();
	}

	TestLighting::~TestLighting()
	{
        glDisable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        delete m_cubeIndexBuffer;
        delete m_cubeShader;
        delete m_cubeVertexArray;
        delete m_cubeTexture;
        delete m_cubeSpecTexture;

        delete m_lightIndexBuffer;
        delete m_lightShader;
        delete m_lightVertexArray;
        delete m_renderer;
	}

	void TestLighting::OnUpdate(float deltaTime)
	{
        m_renderer->Clear();
        m_camera->update();
	}

	void TestLighting::OnRender()
	{
        m_proj = getProjectionMatrix(z_ortho[0], z_ortho[1]);
        auto view = m_camera->getViewMatrix();
        m_lightShader->Bind();
        m_lightShader->SetUniformMat4f("model", m_lightModel);
        m_lightShader->SetUniformMat4f("view", view);
        m_lightShader->SetUniformMat4f("projection", m_proj);
        m_lightShader->SetUniform3f("colour", m_pointLightColor);

        m_cubeShader->Bind();
        m_cubeShader->SetUniformMat4f("view", view);
        m_cubeShader->SetUniformMat4f("projection", m_proj);
        m_cubeShader->SetUniform3f("pointLights[0].position",  m_lightPos);
        m_cubeShader->SetUniform3f("pointLights[0].ambient",  0.3f, 0.3f, 0.3f);
        m_cubeShader->SetUniform3f("pointLights[0].diffuse",  m_pointLightColor);
        m_cubeShader->SetUniform3f("pointLights[0].specular",  1.0f, 1.0f, 1.0f);
        m_cubeShader->SetUniform1f("pointLights[0].constant",  1.0f);
        m_cubeShader->SetUniform1f("pointLights[0].linear",    0.09f);
        m_cubeShader->SetUniform1f("pointLights[0].quadratic", 0.032f);
        m_cubeShader->SetUniform3f("viewPos",  m_camera->getPosition());
        m_cubeShader->SetUniform1f("material.shininess", 32.0f);

        if ( isDirLightOn )
        {
            m_cubeShader->SetUniform3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
            m_cubeShader->SetUniform3f("dirLight.ambient", m_dirLightPower);
            m_cubeShader->SetUniform3f("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
            m_cubeShader->SetUniform3f("dirLight.specular", 0.5f, 0.5f, 0.5f);
        }
        else
            m_cubeShader->SetUniform3f("dirLight.ambient", 0.0f, 0.0f, 0.0f);
        if ( isSpotLightOn )
        {
            m_cubeShader->SetUniform3f("spotLight.position", m_camera->getPosition());
            m_cubeShader->SetUniform3f("spotLight.direction", m_camera->getFront());
            m_cubeShader->SetUniform3f("spotLight.ambient", 0.0f, 0.0f, 0.0f);
            m_cubeShader->SetUniform3f("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
            m_cubeShader->SetUniform3f("spotLight.specular", 1.0f, 1.0f, 1.0f);
            m_cubeShader->SetUniform1f("spotLight.constant", 1.0f);
            m_cubeShader->SetUniform1f("spotLight.linear", 0.09f);
            m_cubeShader->SetUniform1f("spotLight.quadratic", 0.032f);
            m_cubeShader->SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(m_spotLightRadius)));
            m_cubeShader->SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(m_spotLightRadius + 3.0f)));
        }
        else
            m_cubeShader->SetUniform3f("spotLight.diffuse", 0.0f, 0.0f, 0.0f);

        m_cubeTexture->bind(0);
        m_cubeShader->SetUniform1i("material.diffuse", 0);
        m_cubeSpecTexture->bind(1);
        m_cubeShader->SetUniform1i("material.specular", 1);

        m_renderer = Renderer::getInstance();
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_cubeShader->SetUniformMat4f("model", model);
            m_renderer->Draw(*m_cubeVertexArray, *m_cubeIndexBuffer, *m_cubeShader);
        }
        m_renderer->Draw(*m_lightVertexArray, *m_lightIndexBuffer, *m_lightShader);
	}

	void TestLighting::OnImGuiRender()
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

    glm::mat4 TestLighting::getProjectionMatrix(float near_z_bound, float far_z_bound)
    {
        return glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, near_z_bound, far_z_bound);
    }

    void TestLighting::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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

    void TestLighting::mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (!isRunning())
            return;
        m_camera->mouse_callback(window, xpos, ypos);
    }
}

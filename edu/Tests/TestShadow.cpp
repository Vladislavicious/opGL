#include "TestShadow.h"
#include "vBoundBox.h"
#include "pPhysicsScene.h"
#include "loader.h"

namespace test {

	TestShadow::TestShadow()
	{

        z_ortho[0] = 0.01f;
        z_ortho[1] = 70.0f;

        m_proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, z_ortho[0], z_ortho[1]);

		m_textures.push_back(std::make_shared<Texture>("../edu/res/cont.png", "texture_diffuse"));
        m_textures.push_back(std::make_shared<Texture>("../edu/res/spec.png", "texture_specular"));

        auto lightPos = glm::vec3(0.8f, -0.8f, 0.4f);
        auto lightPos1 = glm::vec3(8.8f, 2.3f, 1.4f);
        auto lightPos2 = glm::vec3(3.8f, 1.8f, -0.4f);
        m_pointLights.push_back(std::make_shared<v::PointLight>(lightPos, glm::vec3(0.5f), glm::vec3(0.3f, 0.3f, 0.3f),
                                                glm::vec3(1.0f, 0.0f, 0.0f),
                                                glm::vec3(1.0f), 1.0f, 0.09f, 0.032f, "../edu/res/cube/cube.obj",
                                                "../edu/res/lightShader.vs", "../edu/res/lightShader.fs"));
        m_pointLights.push_back(std::make_shared<v::PointLight>(lightPos1, glm::vec3(0.5f), glm::vec3(0.3f, 0.3f, 0.3f),
                                                glm::vec3(0.0f, 1.0f, 0.0f),
                                                glm::vec3(1.0f), 1.0f, 0.09f, 0.032f, "../edu/res/cube/cube.obj",
                                                "../edu/res/lightShader.vs", "../edu/res/lightShader.fs"));
        m_pointLights.push_back(std::make_shared<v::PointLight>(lightPos2, glm::vec3(0.5f), glm::vec3(0.3f, 0.3f, 0.3f),
                                                glm::vec3(0.0f, 0.0f, 1.0f),
                                                glm::vec3(1.0f), 1.0f, 0.09f, 0.032f, "../edu/res/cube/cube.obj",
                                                "../edu/res/lightShader.vs", "../edu/res/lightShader.fs"));
        m_directLight = std::make_unique<v::DirLight>(m_dirLightPower, glm::vec3(0.4f, 0.4f, 0.4f),
                                                    glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.2f, -1.0f, -0.3f));

        m_spotLight = std::make_unique<v::SpotLight>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.4f, 0.4f, 0.4f),
                                                    glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.8f),
                                                    1.0f, 0.09f, 0.032f, 12.0f, 15.0f);


        m_dirLightPower = glm::vec3(0.95f, 0.0f, 0.0f);
        m_modelMovement = glm::vec3(0.05f, 0.05f, 3.05f);

        m_Player = std::make_shared<v::Player>(glm::vec3(1.0f, 4.0f, 0.5f), glm::vec3(1.0f),
                                                "../edu/res/Ancient_Vase.obj", "../edu/res/meshShader.vs",
                                                "../edu/res/meshShader.fs");
        m_Player->addBoundBox(glm::vec3(0.0f), glm::vec3(0.6f, 1.0f, 0.4f), false, true, true, true);
        m_models.push_back(m_Player);
        auto temp = std::make_shared<v::DynamicModel>(glm::vec3(4.0f, 6.0f, 3.5f), glm::vec3(1.0f),
                                                "../edu/res/Ancient_Vase.obj", "../edu/res/meshShader.vs",
                                                "../edu/res/meshShader.fs");
        temp->addBoundBox(glm::vec3(0.0f), glm::vec3(0.6f, 1.0f, 0.4f), false, false, false, false);
        m_models.push_back(temp);
        temp = std::make_shared<v::DynamicModel>(glm::vec3(-3.0f, 4.0f, 2.5f), glm::vec3(1.0f),
                                                "../edu/res/Ancient_Vase.obj", "../edu/res/meshShader.vs",
                                                "../edu/res/meshShader.fs");
        temp->addBoundBox(glm::vec3(0.0f), glm::vec3(0.6f, 1.0f, 0.4f), false, false, false, false);
        m_models.push_back(temp);
        temp = std::make_shared<v::DynamicModel>(glm::vec3(-3.0f, 5.0f, -5.5f), glm::vec3(1.0f),
                                                "../edu/res/Ancient_Vase.obj", "../edu/res/meshShader.vs",
                                                "../edu/res/meshShader.fs");
        temp->addBoundBox(glm::vec3(0.0f), glm::vec3(0.6f, 1.0f, 0.4f), false, false, false, false);
        m_models.push_back(temp);
        temp = std::make_shared<v::DynamicModel>(glm::vec3(1.7f, 8.0f, -6.5f), glm::vec3(1.0f),
                                                "../edu/res/Ancient_Vase.obj", "../edu/res/meshShader.vs",
                                                "../edu/res/meshShader.fs");
        temp->addBoundBox(glm::vec3(0.0f), glm::vec3(0.6f, 1.0f, 0.4f), false, false, false, false);
        m_models.push_back(temp);

        auto scene = v::PhysicScene::getInstance();
        float planeSize = 15.0f;
        scene->addWorldBorder(planeSize);

        float a = glfwGetTime();
        v::Loader::processLoadQueue();
        std::cout << "Time: " << glfwGetTime() - a << std::endl;

        Toggle();
	}

	TestShadow::~TestShadow()
	{
        auto scene = v::PhysicScene::getInstance();
        delete scene;
        Texture::deleteTextures();
	}

	void TestShadow::OnUpdate(float deltaTime)
	{
        if (!isRunning())
            return;
        auto renderer = Renderer::getInstance();
        renderer->Clear();
        auto scene = v::PhysicScene::getInstance();
        scene->Step();
        time_elapsed += deltaTime;
        m_Player->Update();
        if (time_elapsed >= scene->getFrameTime() )
        {
            time_elapsed = 0.0f;
            m_Player->Move();
        }
	}

	void TestShadow::OnRender()
	{
        if (!isRunning())
            return;
        m_proj = m_Player->getProjectionMatrix();
        auto view = m_Player->getViewMatrix();
        for (auto& pointLight : m_pointLights)
        {
            pointLight->ToDrawShader(view, m_proj);
            pointLight->Draw();
        }
        for (auto& model : m_models)
        {
            model->ToDrawShader(view, m_proj);
            auto modelShader = model->getShader();
            modelShader->Bind();

            modelShader->SetUniform1i("pointLightsNumber", m_pointLights.size());
            int i = 0;
            for (auto& pointLight : m_pointLights)
            {
                pointLight->ToObjectShader(*modelShader, "pointLights[" + std::to_string(i++) +"]");
            }

            modelShader->SetUniform3f("viewPos",  m_Player->getCameraPosition());

            modelShader->SetUniform1f("material.shininess", 32.0f);

            m_directLight->setLightColor(m_dirLightPower);
            m_directLight->ToObjectShader(*modelShader, "dirLight");

            m_spotLight->setLightDirection(m_Player->getFront());
            m_spotLight->setLightPosition(m_Player->getCameraPosition());
            m_spotLight->ToObjectShader(*modelShader, "spotLight");

            m_textures[0]->bind(0);
            modelShader->SetUniform1i("material.texture_diffuse1", 0);
            m_textures[1]->bind(1);
            modelShader->SetUniform1i("material.texture_specular1", 1);

            model->Draw();
        }

        if ( bBoxesVisible )
        {
            auto scene = v::PhysicScene::getInstance();
            scene->ToDrawShader(view, m_proj);
            scene->Draw();
        }
	}

	void TestShadow::OnImGuiRender()
	{
        ImGui::SetWindowCollapsed(isRunning());
        if (isRunning())
            return;

        if (ImGui::Button("bBoxes"))
            bBoxesVisible = !bBoxesVisible;

        if (ImGui::Button("delete"))
            m_Player->deleteBoundBox();

        ImGui::SliderFloat3("Object movement", &m_modelMovement.x, -10.0f, 10.0f, "%.2f");
        ImGui::SliderFloat3("light colour", &m_pointLights[0]->getLightColor().x, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat3("directional light", &m_dirLightPower.x, 0.0f, 1.0f, "%.2f");
	}

    void TestShadow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            if (isRunning())
            {
                Toggle();
                m_Player->ToggleCamera();
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
                m_Player->ToggleCamera();
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                return;
            }
        }
        if (!isRunning())
            return;
        m_Player->key_callback(window, key, scancode, action, mods);
    }

    void TestShadow::mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (!isRunning())
            return;
        m_Player->mouse_callback(window, xpos, ypos);
    }

    void TestShadow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (!isRunning())
            return;
        m_Player->mouse_button_callback(window, button, action, mods);
    }
}

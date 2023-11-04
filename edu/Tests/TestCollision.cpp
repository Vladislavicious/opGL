#include "TestCollision.h"
#include "vBoundBox.h"
#include "pPhysicsScene.h"
extern float deltaTime;

namespace test {

	TestCollision::TestCollision()
	{
        m_renderer = Renderer::getInstance();
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        z_ortho[0] = 0.01f;
        z_ortho[1] = 100.0f;

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

        m_camera = std::make_unique<myCamera>();

        m_dirLightPower = glm::vec3(0.95f, 0.0f, 0.0f);
        m_modelMovement = glm::vec3(0.05f, 0.05f, 3.05f);

        m_myModel = std::make_unique<v::DynamicModel>(glm::vec3(1.0f, 4.0f, 0.5f), glm::vec3(1.0f),
                                                "../edu/res/Ancient_Vase.obj", "../edu/res/meshShader.vs",
                                                "../edu/res/meshShader.fs");
        m_myModel->addBoundBox(glm::vec3(0.0f), glm::vec3(0.6f), false);

        auto scene = v::PhysicScene::getInstance();
        scene->getBbox(glm::vec3(0.0f), glm::vec3(10.0f, 1.0f, 10.0f), true);
        int a = 5;
	}

	TestCollision::~TestCollision()
	{
        glDisable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        delete m_renderer;
	}

	void TestCollision::OnUpdate(float deltaTime)
	{
        auto scene = v::PhysicScene::getInstance();
        scene->Step();
        m_renderer->Clear();
	}

	void TestCollision::OnRender()
	{
        m_proj = getProjectionMatrix(z_ortho[0], z_ortho[1]);
        auto view = m_camera->getViewMatrix();
        for (auto& pointLight : m_pointLights)
            pointLight->ToDrawShader(view, m_proj);

        m_myModel->ToDrawShader(view, m_proj);
        auto modelShader = m_myModel->getShader();

        modelShader->SetUniform1i("pointLightsNumber", m_pointLights.size());
        int i = 0;
        for (auto& pointLight : m_pointLights)
        {
            pointLight->ToObjectShader(*modelShader, "pointLights[" + std::to_string(i++) +"]");
        }

        modelShader->SetUniform3f("viewPos",  m_camera->getPosition());

		modelShader->SetUniform1f("material.shininess", 32.0f);

        m_directLight->setLightColor(m_dirLightPower);
        m_directLight->ToObjectShader(*modelShader, "dirLight");

        m_spotLight->setLightDirection(m_camera->getFront());
        m_spotLight->setLightPosition(m_camera->getPosition());
        m_spotLight->ToObjectShader(*modelShader, "spotLight");

		m_textures[0]->bind(0);
        modelShader->SetUniform1i("material.texture_diffuse1", 0);
        m_textures[1]->bind(1);
        modelShader->SetUniform1i("material.texture_specular1", 1);

        m_myModel->Draw();

        for (auto& pointLight : m_pointLights)
            pointLight->Draw();

        if ( bBoxesVisible )
        {
            auto scene = v::PhysicScene::getInstance();
            scene->ToDrawShader(view, m_proj);
            scene->Draw();
        }
	}

	void TestCollision::OnImGuiRender()
	{
        ImGui::SetWindowCollapsed(m_camera->active);
        if (m_camera->active)
            return;

        if (ImGui::Button("add_body"))
            addBody();

        if (ImGui::Button("bBoxes"))
            bBoxesVisible = !bBoxesVisible;

        ImGui::SliderFloat3("Object movement", &m_modelMovement.x, -10.0f, 10.0f, "%.2f");
        ImGui::SliderFloat3("light colour", &m_pointLights[0]->getLightColor().x, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat3("directional light", &m_dirLightPower.x, 0.0f, 1.0f, "%.2f");

        auto& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}

    void TestCollision::addBody()
    {
        auto scene = v::PhysicScene::getInstance();
        scene->getBbox(m_camera->getPosition() + m_camera->getFront() * 3.0f, glm::vec3(1.0f), false);
    }

    glm::mat4 TestCollision::getProjectionMatrix(float near_z_bound, float far_z_bound)
    {
        return glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, near_z_bound, far_z_bound);
    }

    void TestCollision::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose (window, 1);
        }
        m_camera->key_callback(window, key, scancode, action, mods);
    }

    void TestCollision::mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        m_camera->mouse_callback(window, xpos, ypos);
    }

    void TestCollision::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (!m_camera->active)
            return;
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
            addBody();
    }
}

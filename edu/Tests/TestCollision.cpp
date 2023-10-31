#include "TestCollision.h"

extern float deltaTime;

namespace test {

	TestCollision::TestCollision()
	{
        m_renderer = std::make_shared<Renderer>();
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        z_ortho[0] = 0.01f;
        z_ortho[1] = 12.0f;

        m_proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, z_ortho[0], z_ortho[1]);

		m_textures.push_back(std::make_shared<Texture>("../edu/res/cont.png", "texture_diffuse"));
        m_textures.push_back(std::make_shared<Texture>("../edu/res/spec.png", "texture_specular"));

        auto lightPos = glm::vec3(0.8f, -0.8f, 0.4f);
        auto lightPos1 = glm::vec3(8.8f, 2.3f, 1.4f);
        auto lightPos2 = glm::vec3(3.8f, 1.8f, -0.4f);
        m_pointLights.push_back(std::make_shared<v::PointLight>(lightPos, glm::vec3(0.5f), glm::vec3(0.3f, 0.3f, 0.3f),
                                                glm::vec3(1.0f, 0.0f, 0.0f),
                                                glm::vec3(1.0f), 1.0f, 0.09f, 0.032f, "../edu/res/cube/cube.obj",
                                                "../edu/res/lightShader.vs", "../edu/res/lightShader.fs",
                                                m_renderer));
        m_pointLights.push_back(std::make_shared<v::PointLight>(lightPos1, glm::vec3(0.5f), glm::vec3(0.3f, 0.3f, 0.3f),
                                                glm::vec3(0.0f, 1.0f, 0.0f),
                                                glm::vec3(1.0f), 1.0f, 0.09f, 0.032f, "../edu/res/cube/cube.obj",
                                                "../edu/res/lightShader.vs", "../edu/res/lightShader.fs",
                                                m_renderer));
        m_pointLights.push_back(std::make_shared<v::PointLight>(lightPos2, glm::vec3(0.5f), glm::vec3(0.3f, 0.3f, 0.3f),
                                                glm::vec3(0.0f, 0.0f, 1.0f),
                                                glm::vec3(1.0f), 1.0f, 0.09f, 0.032f, "../edu/res/cube/cube.obj",
                                                "../edu/res/lightShader.vs", "../edu/res/lightShader.fs",
                                                m_renderer));
        m_directLight = std::make_unique<v::DirLight>(m_dirLightPower, glm::vec3(0.4f, 0.4f, 0.4f),
                                                    glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.2f, -1.0f, -0.3f));

        m_spotLight = std::make_unique<v::SpotLight>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.4f, 0.4f, 0.4f),
                                                    glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.8f),
                                                    1.0f, 0.09f, 0.032f, 12.0f, 15.0f);

        m_bBoxes.push_back(std::make_shared<v::Object>(glm::vec3(-0.8f, -0.8f, 1.4f), glm::vec3(0.5f),
                                                "../edu/res/cube/cube.obj", "../edu/res/lightShader.vs",
                                                "../edu/res/lightShader.fs", m_renderer));
        m_bBoxes.push_back(std::make_shared<v::Object>(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f),
                                                "../edu/res/plane/plane.obj", "../edu/res/lightShader.vs",
                                                "../edu/res/lightShader.fs", m_renderer));
		m_camera = std::make_unique<myCamera>();

        m_dirLightPower = glm::vec3(0.95f, 0.0f, 0.0f);
        m_modelMovement = glm::vec3(0.05f, 0.05f, 3.05f);

        m_modelShader = new Shader("../edu/res/meshShader.vs", "../edu/res/meshShader.fs");

        m_myModel = new myModel("../edu/res/Ancient_Vase.obj");

	}

	TestCollision::~TestCollision()
	{
        glDisable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        delete m_modelShader;

        delete m_myModel;
	}

	void TestCollision::OnUpdate(float deltaTime)
	{
        m_renderer->Clear();
	}

	void TestCollision::OnRender()
	{
        m_proj = getProjectionMatrix(z_ortho[0], z_ortho[1]);
        auto view = m_camera->getViewMatrix();
        for (auto& pointLight : m_pointLights)
            pointLight->ToDrawShader(view, m_proj);


        for (auto& box : m_bBoxes)
        {
            box->setPos(m_modelMovement);
            box->ToDrawShader(view, m_proj);
        }

        m_modelShader->Bind();
        auto modelPlace = glm::translate(glm::mat4(1.0f), m_modelMovement);
        m_modelShader->SetUniformMat4f("model", modelPlace);
        m_modelShader->SetUniformMat4f("view", view);
        m_modelShader->SetUniformMat4f("projection", m_proj);

        int i = 0;
        m_modelShader->SetUniform1i("pointLightsNumber", m_pointLights.size());
        for (auto& pointLight : m_pointLights)
        {
            pointLight->ToObjectShader(*m_modelShader, "pointLights[" + std::to_string(i++) +"]");
        }

        m_modelShader->SetUniform3f("viewPos",  m_camera->getPosition());


		m_modelShader->SetUniform1f("material.shininess", 32.0f);

        m_directLight->setLightColor(m_dirLightPower);
        m_directLight->ToObjectShader(*m_modelShader, "dirLight");

        m_spotLight->setLightDirection(m_camera->getFront());
        m_spotLight->setLightPosition(m_camera->getPosition());
        m_spotLight->ToObjectShader(*m_modelShader, "spotLight");

		m_textures[0]->bind(0);
        m_modelShader->SetUniform1i("material.texture_diffuse1", 0);
        m_textures[1]->bind(1);
        m_modelShader->SetUniform1i("material.texture_specular1", 1);

        m_renderer->Draw(*m_myModel, *m_modelShader);

        for (auto& pointLight : m_pointLights)
            pointLight->Draw();

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(10.0f);
        for (auto& box : m_bBoxes)
            box->Draw();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void TestCollision::OnImGuiRender()
	{
        ImGui::SetWindowCollapsed(m_camera->active);
        if (m_camera->active)
            return;

        ImGui::SliderFloat3("Object movement", &m_modelMovement.x, -10.0f, 10.0f, "%.2f");
        ImGui::SliderFloat3("light colour", &m_pointLights[0]->getLightColor().x, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat3("directional light", &m_dirLightPower.x, 0.0f, 1.0f, "%.2f");

        auto& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
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
}

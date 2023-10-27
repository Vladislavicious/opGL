#include "TestPR6.h"

namespace test {

	TestPR6::TestPR6()
	{

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        z_ortho[0] = 0.01f;
        z_ortho[1] = 12.0f;

        m_proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, z_ortho[0], z_ortho[1]);

        auto lightPos = glm::vec3(0.8f, -0.8f, 0.4f);
        auto lightPos1 = glm::vec3(8.8f, 2.3f, 1.4f);
        auto lightPos2 = glm::vec3(3.8f, 1.8f, -0.4f);
        m_pointLights.push_back(std::make_shared<PointLight>(lightPos, glm::vec3(0.3f, 0.3f, 0.3f),
                                                glm::vec3(1.0f, 0.0f, 0.0f),
                                                glm::vec3(1.0f), 1.0f, 0.09f, 0.032f, 0.4f,
                                                "../edu/res/lightShader.shader"));
        m_pointLights.push_back(std::make_shared<PointLight>(lightPos1, glm::vec3(0.3f, 0.3f, 0.3f),
                                                glm::vec3(0.0f, 1.0f, 0.0f),
                                                glm::vec3(1.0f), 1.0f, 0.09f, 0.032f, 0.4f,
                                                "../edu/res/lightShader.shader"));
        m_pointLights.push_back(std::make_shared<PointLight>(lightPos2, glm::vec3(0.3f, 0.3f, 0.3f),
                                                glm::vec3(0.0f, 0.0f, 1.0f),
                                                glm::vec3(1.0f), 1.0f, 0.09f, 0.032f, 0.4f,
                                                "../edu/res/lightShader.shader"));

        m_spotLightRadius = 12.0f;
        m_dirLightPower = glm::vec3(0.05f, 0.05f, 0.05f);
        m_modelMovement = glm::vec3(0.05f, 0.05f, 3.05f);

        m_modelShader = new Shader("../edu/res/PR6/sphereShader.shader");

        m_myModel = new myModel("../edu/res/PR6/pinkSphere.obj");

        m_renderer = new Renderer();
	}

	TestPR6::~TestPR6()
	{
        glDisable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        delete m_modelShader;

        delete m_myModel;

        delete m_renderer;
	}

	void TestPR6::OnUpdate(float deltaTime)
	{
        m_renderer->Clear();
	}

	void TestPR6::OnRender()
	{
        m_proj = getProjectionMatrix(z_ortho[0], z_ortho[1]);
        auto view = myCamera::getViewMatrix();
        for (auto& pointLight : m_pointLights)
            pointLight->ToLightShader(view, m_proj);

        m_modelShader->Bind();
        auto modelPlace = glm::translate(glm::mat4(1.0f), m_modelMovement);
        auto sphereColour = glm::vec3(0.9f, 0.3f, 0.3f);
        m_modelShader->SetUniform3f("sphereColour", sphereColour);
        m_modelShader->SetUniformMat4f("model", modelPlace);
        m_modelShader->SetUniformMat4f("view", view);
        m_modelShader->SetUniformMat4f("projection", m_proj);

        int i = 0;
        for (auto& pointLight : m_pointLights)
        {
            pointLight->ToObjectShader(*m_modelShader, "pointLights[" + std::to_string(i++) +"]");
        }

        m_modelShader->SetUniform3f("viewPos",  myCamera::getPosition());

        if ( isMaterial )
        {
            auto temp = glm::vec3(1.0f, 1.0f, 1.0f);
            m_modelShader->SetUniform3f("material.ambient", temp);
            temp = glm::vec3(0.3f, 0.3f, 0.3f);
            m_modelShader->SetUniform3f("material.diffuse", temp);
            glm::vec3(1.0f, 1.0f, 1.0f);
            m_modelShader->SetUniform3f("material.specular", temp);
            m_modelShader->SetUniform1f("material.shininess", 32.0f);
        }
        else
        {
            auto temp = glm::vec3(0.1f, 0.1f, 0.1f);
            m_modelShader->SetUniform3f("material.ambient", temp);
            temp = glm::vec3(0.3f, 0.3f, 0.3f);
            m_modelShader->SetUniform3f("material.diffuse", temp);
            glm::vec3(0.0f, 0.0f, 0.0f);
            m_modelShader->SetUniform3f("material.specular", temp);
            m_modelShader->SetUniform1f("material.shininess", 1.0f);
        }

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
            m_modelShader->SetUniform3f("spotLight.position", myCamera::getPosition());
            m_modelShader->SetUniform3f("spotLight.direction", myCamera::getFront());
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

        m_renderer->Draw(*m_myModel, *m_modelShader);
        for (auto& pointLight : m_pointLights)
            m_renderer->Draw(pointLight->getModel(), pointLight->getShader());
	}

	void TestPR6::OnImGuiRender()
	{
        ImGui::SetWindowCollapsed(myCamera::active);
        if (myCamera::active)
            return;

        if ( ImGui::Button("DirLight"))
            isDirLightOn = !isDirLightOn;

        if ( ImGui::Button("SpotLight"))
            isSpotLightOn = !isSpotLightOn;

        if ( ImGui::Button("Material"))
            isMaterial = !isMaterial;

        ImGui::SliderFloat3("Object movement", &m_modelMovement.x, -10.0f, 10.0f, "%.2f");
        ImGui::SliderFloat3("light colour", &m_pointLights[0]->getLightColor().x, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat3("directional light", &m_dirLightPower.x, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat("spotLight radius", &m_spotLightRadius, 10.0f, 50.0f, "%.2f");

        auto& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}

    glm::mat4 TestPR6::getProjectionMatrix(float near_z_bound, float far_z_bound)
    {
        return glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, near_z_bound, far_z_bound);
    }
}

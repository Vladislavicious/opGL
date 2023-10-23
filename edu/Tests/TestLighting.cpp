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

        m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);

        z_ortho[0] = 0.01f;
        z_ortho[1] = 10.0f;

        m_proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, z_ortho[0], z_ortho[1]);
        m_cubeModel = glm::mat4(1.0f);
        m_cubeTexture = new Texture("../edu/res/cont.png");
        m_cubeSpecTexture = new Texture("../edu/res/spec.png");

        m_lightPos = glm::vec3(-0.8f, 0.8f, 0.4f);
        m_lightModel = glm::translate(glm::mat4(1.0f), m_lightPos);
        m_lightModel = glm::scale(m_lightModel, glm::vec3(0.4f));
        m_lightColor = glm::vec3(1.0f, 0.0f, 0.0f);

        m_cubeShader = new Shader("../edu/res/cubeShader.shader");

        m_lightShader = new Shader("../edu/res/lightShader.shader");


        m_renderer = new Renderer();
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
	}

	void TestLighting::OnRender()
	{
        m_proj = getProjectionMatrix(z_ortho[0], z_ortho[1]);
        auto view = myCamera::getViewMatrix();
        m_lightShader->Bind();
        m_lightShader->SetUniformMat4f("model", m_lightModel);
        m_lightShader->SetUniformMat4f("view", view);
        m_lightShader->SetUniformMat4f("projection", m_proj);
        m_lightShader->SetUniform3f("colour", m_lightColor);

        m_cubeModel = glm::rotate(m_cubeModel, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        m_cubeModel = glm::rotate(m_cubeModel, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        m_cubeModel = glm::rotate(m_cubeModel, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        m_cubeShader->Bind();
        m_cubeShader->SetUniformMat4f("model", m_cubeModel);
        m_cubeShader->SetUniformMat4f("view", view);
        m_cubeShader->SetUniformMat4f("projection", m_proj);
        m_cubeShader->SetUniform3f("light.position",  m_lightPos);
        m_cubeShader->SetUniform3f("light.ambient",  0.3f, 0.3f, 0.3f);
        m_cubeShader->SetUniform3f("light.diffuse",  m_lightColor);
        m_cubeShader->SetUniform3f("light.specular",  1.0f, 1.0f, 1.0f);
        m_cubeShader->SetUniform1f("light.constant",  1.0f);
        m_cubeShader->SetUniform1f("light.linear",    0.09f);
        m_cubeShader->SetUniform1f("light.quadratic", 0.032f);
        m_cubeShader->SetUniform3f("viewPos",  myCamera::getPosition());
        m_cubeShader->SetUniform1f("material.shininess", 32.0f);
        m_cubeTexture->bind(0);
        m_cubeShader->SetUniform1i("material.diffuse", 0);
        m_cubeSpecTexture->bind(1);
        m_cubeShader->SetUniform1i("material.specular", 1);

        m_renderer->Draw(*m_lightVertexArray, *m_lightIndexBuffer, *m_lightShader);
        m_renderer->Draw(*m_cubeVertexArray, *m_cubeIndexBuffer, *m_cubeShader);
	}

	void TestLighting::OnImGuiRender()
	{
        ImGui::SetWindowCollapsed(myCamera::active);
        if (myCamera::active)
            return;

        ImGui::InputFloat2("Z:", z_ortho, "%.1f");
        ImGui::SliderFloat3("model rotation around XYZ", &m_rotation.x, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat3("light colour", &m_lightColor.x, 0.0f, 1.0f, "%.2f");

        auto& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}

    glm::mat4 TestLighting::getProjectionMatrix(float near_z_bound, float far_z_bound)
    {
        return glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, near_z_bound, far_z_bound);
    }
}

#include "TestMovingSquare.h"

namespace test {

	TestMovingSquare::TestMovingSquare()
	{

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

        m_squareVertexArray = new VertexArray();
        m_squareVertexArray->AddBuffer(squareBuffer, vbLayout);
        unsigned int squareIndices[] = {
            0, 1, 2,
            2, 3, 0
        };

        m_squareIndexBuffer = new IndexBuffer(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));
        m_squareVertexArray->UnBind();
        squareBuffer.UnBind();
        m_squareIndexBuffer->UnBind();



        m_proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
        m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, -0.4f, 0.0f));
        m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, 0.5f, 0.0f));

        m_mvp = m_proj * m_view * m_model;
        m_translation = glm::vec3(0.0f, 0.5f, 0.0f);

        m_shader = new Shader("../edu/res/BasicShader.shader");

        m_renderer = new Renderer();
	}

	TestMovingSquare::~TestMovingSquare()
	{
        delete m_squareIndexBuffer;
        delete m_shader;
        delete m_squareVertexArray;
        delete m_renderer;
	}

	void TestMovingSquare::OnUpdate(float deltaTime)
	{
        m_renderer->Clear();
	}

	void TestMovingSquare::OnRender()
	{
        m_model = glm::translate(glm::mat4(1.0f), m_translation);
        m_mvp = m_proj * m_view * m_model;

        m_shader->Bind();
        m_shader->SetUniformMat4f("u_MVP", m_mvp);

        m_renderer->Draw(*m_squareVertexArray, *m_squareIndexBuffer, *m_shader);
	}

	void TestMovingSquare::OnImGuiRender()
	{
        ImGui::SliderFloat2("model position", &m_translation.x, -1.0f, 1.0f);

        auto& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}

}

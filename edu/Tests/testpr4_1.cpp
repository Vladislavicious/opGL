#include "testpr4_1.h"

namespace test {

	TestPR4_1::TestPR4_1()
	{
        VertexBufferLayout vbLayout;
        vbLayout.Push<float>(3); // 3 координаты
        vbLayout.Push<float>(3); // 3 цвета

        GLfloat square[] = {
            -0.6f, -0.6f, -0.2f, 0.6f, 0.1f, 0.5f,
            0.6f, -0.6f, -0.2f, 0.5f, 0.4f, 0.3f,
             0.6f, 0.6f, -0.2f, 0.9f, 0.3f, 0.3f,
             -0.6f, 0.6f, -0.2f, 0.2f, 0.1f, 0.3f,
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

        GLfloat square1[] = {
            -0.5f, 0.8f, -0.8f, 0.3f, 0.2f, 0.1f,
            0.5f, 0.8f, 0.8f, 0.5f, 0.9f, 0.1f,
             0.5f, -0.8f, 0.8f, 0.1f, 0.3f, 0.6f,
             -0.5f, -0.8f, -0.8f, 0.1f, 0.1f, 0.9f,
        };

        auto square1Buffer = VertexBuffer(square1, sizeof(square1));

        m_square1VertexArray = new VertexArray();
        m_square1VertexArray->AddBuffer(square1Buffer, vbLayout);


        m_square1VertexArray->UnBind();
        square1Buffer.UnBind();


        GLfloat triangle[] = {
            -1.0f, 1.0f, 0.0f, 0.5f, 0.2f, 0.7f,
            0.0f, 1.0f, 1.0f, 0.5f, 0.2f, 0.3f,
             1.0f, 0.0f, 0.0f, 0.4f, 0.9f, 0.6f,
        };

        auto triangleBuffer = VertexBuffer(triangle, sizeof(triangle));

        m_triangleVertexArray = new VertexArray();
        m_triangleVertexArray->AddBuffer(triangleBuffer, vbLayout);

        unsigned int triangleIndices[] = {
            0, 1, 2
        };

        m_triangleIndexBuffer = new IndexBuffer(triangleIndices, sizeof(triangleIndices) / sizeof(unsigned int));
        triangleBuffer.UnBind();
        m_triangleVertexArray->UnBind();
        m_triangleIndexBuffer->UnBind();

        auto m_proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
        auto m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, -0.4f, 0.0f));
        auto m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, 0.5f, 0.0f));

        auto m_mvp = m_proj * m_view * m_model;

        m_shader = new Shader("../edu/res/BasicShader.shader");
        m_shader->Bind();
        m_shader->SetUniformMat4f("u_MVP", m_mvp);

        m_renderer = new Renderer();
	}

	TestPR4_1::~TestPR4_1()
	{
        delete m_squareIndexBuffer;
        delete m_triangleIndexBuffer;
        delete m_shader;
        delete m_squareVertexArray;
        delete m_square1VertexArray;
        delete m_triangleVertexArray;
        delete m_renderer;
	}

	void TestPR4_1::OnUpdate(float deltaTime)
	{
        m_renderer->Clear();
	}

	void TestPR4_1::OnRender()
	{
        m_renderer->Draw(*m_squareVertexArray, *m_squareIndexBuffer, *m_shader);

        m_renderer->Draw(*m_square1VertexArray, *m_squareIndexBuffer, *m_shader);

        m_renderer->Draw(*m_triangleVertexArray, *m_triangleIndexBuffer, *m_shader);
	}

	void TestPR4_1::OnImGuiRender()
	{
        if (!enabled)
        {
            if ( ImGui::Button("Enable depth test") )
            {
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);
                enabled = true;
            }
        }
        else
        {
            if ( ImGui::Button("Disable depth test") )
            {
                glDisable(GL_DEPTH_TEST);
                enabled = false;
            }
        }

        auto& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}

}

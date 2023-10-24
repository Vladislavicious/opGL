#include "TestCube.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

namespace test {

	TestCube::TestCube()
	{

                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);

                VertexBufferLayout vbLayout;
                vbLayout.Push<float>(3); // 3 координаты
                vbLayout.Push<float>(3); // 3 цвета

                GLfloat cube[] = {
                -0.5f,  0.5f, -0.5f, 0.5f, 0.1f, 0.5f, // V0
                -0.5f, -0.5f, -0.5f, 0.4f, 0.3f, 0.1f, // V1
                0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.6f, // V2
                0.5f,  0.5f, -0.5f, 0.1f, 0.3f, 0.9f, // V3
                -0.5f,  0.5f,  0.5f, 0.3f, 0.1f, 0.8f, // V4
                -0.5f, -0.5f,  0.5f, 0.6f, 0.7f, 0.2f, // V5
                0.5f, -0.5f,  0.5f, 0.2f, 0.4f, 0.1f, // V6
                0.5f,  0.5f,  0.5f, 0.9f, 0.5f, 0.0f, // V7
                };

                auto squareBuffer = VertexBuffer(cube, sizeof(cube));

                m_cubeVertexArray = new VertexArray();
                m_cubeVertexArray->AddBuffer(squareBuffer, vbLayout);
                unsigned int cubeIndices[] = {
                0, 1, 2,
                2, 3, 0,

                4, 7, 6,
                6, 5, 4,

                4, 0, 3,
                3, 7, 4,

                1, 5, 6,
                6, 2, 1,

                3, 2, 6,
                6, 7, 3,

                4, 5, 1,
                1, 0, 4
                };

                m_cubeIndexBuffer = new IndexBuffer(cubeIndices, sizeof(cubeIndices) / sizeof(unsigned int));
                m_cubeVertexArray->UnBind();
                squareBuffer.UnBind();
                m_cubeIndexBuffer->UnBind();

                m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);

                m_proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
                m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
                m_model = glm::mat4(1.0f);
                m_mvp = m_proj * m_view * m_model;

                m_shader = new Shader("../edu/res/BasicShader.shader");

                m_renderer = new Renderer();
	}

	TestCube::~TestCube()
	{
                delete m_cubeIndexBuffer;
                delete m_shader;
                delete m_cubeVertexArray;
                delete m_renderer;
	}

	void TestCube::OnUpdate(float deltaTime)
	{
                m_renderer->Clear();
	}

	void TestCube::OnRender()
	{
                m_model = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
                m_model = glm::rotate(m_model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
                m_model = glm::rotate(m_model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
                m_mvp = m_proj * m_view * m_model;

                m_shader->Bind();
                m_shader->SetUniformMat4f("u_MVP", m_mvp);

                m_renderer->Draw(*m_cubeVertexArray, *m_cubeIndexBuffer, *m_shader);
	}

	void TestCube::OnImGuiRender()
	{
                ImGui::SliderFloat("model rotation around X", &m_rotation.x, 0.0f, 360.0f);
                ImGui::SliderFloat("model rotation around Y", &m_rotation.y, 0.0f, 360.0f);
                ImGui::SliderFloat("model rotation around Z", &m_rotation.z, 0.0f, 360.0f);

                auto& io = ImGui::GetIO();
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}

}

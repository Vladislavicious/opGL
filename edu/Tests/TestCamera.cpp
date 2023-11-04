#include "TestCamera.h"

namespace test {

	TestCamera::TestCamera()
	{
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

        x_ortho[0] = y_ortho[0] = -1.0f;
        x_ortho[1] = y_ortho[1] = 1.0f;
        z_ortho[0] = 0.01f;
        z_ortho[1] = 10.0f;

        m_camera = std::make_unique<myCamera>();

        m_proj = glm::ortho(x_ortho[0], x_ortho[1], y_ortho[0],
                        y_ortho[1], z_ortho[0], z_ortho[1]);
        m_model = glm::mat4(1.0f);
        m_mvp = m_proj * m_camera->getViewMatrix() * m_model;

        m_shader = new Shader("../edu/res/BasicShader.vs", "../edu/res/BasicShader.fs");

        m_renderer = Renderer::getInstance();
	}

	TestCamera::~TestCamera()
	{
        glDisable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        delete m_cubeIndexBuffer;
        delete m_shader;
        delete m_cubeVertexArray;
        delete m_renderer;
	}

	void TestCamera::OnUpdate(float deltaTime)
	{
        m_renderer->Clear();
        m_camera->updatePosition();
	}

	void TestCamera::OnRender()
	{
        m_proj = getProjectionMatrix(x_ortho, y_ortho, z_ortho);
        m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, m_translationZ));
        m_model = glm::rotate(m_model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        m_model = glm::rotate(m_model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        m_model = glm::rotate(m_model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        m_mvp = m_proj * m_camera->getViewMatrix() * m_model;

        m_shader->Bind();
        m_shader->SetUniformMat4f("u_MVP", m_mvp);

        m_renderer = Renderer::getInstance();
        m_renderer->Draw(*m_cubeVertexArray, *m_cubeIndexBuffer, *m_shader);
	}

	void TestCamera::OnImGuiRender()
	{
        ImGui::SetWindowCollapsed(m_camera->active);
        if (m_camera->active)
        {
                return;
        }
        if ( ortho )
        {
                if( ImGui::Button("Perspective view") )
                        ortho = false;
        }
        else
        {
                if( ImGui::Button("Ortho view") )
                        ortho = true;
        }


        ImGui::InputFloat2("X:", x_ortho, "%.1f");
        ImGui::InputFloat2("Y:", y_ortho, "%.1f");
        ImGui::InputFloat2("Z:", z_ortho, "%.1f");

        ImGui::SliderFloat("model rotation around X", &m_rotation.x, 0.0f, 360.0f);
        ImGui::SliderFloat("model rotation around Y", &m_rotation.y, 0.0f, 360.0f);
        ImGui::SliderFloat("model rotation around Z", &m_rotation.z, 0.0f, 360.0f);

        ImGui::SliderFloat("model translation around Z", &m_translationZ, 0.0f, -10.0f);

        auto& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	}

    glm::mat4 TestCamera::getProjectionMatrix(float *x_bounds, float *y_bounds, float *z_bounds)
    {
        if ( ortho )
                return glm::ortho(x_bounds[0], x_bounds[1], y_bounds[0],
                                y_bounds[1], z_bounds[0], z_bounds[1]);

        return glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, z_bounds[0], z_bounds[1]);
    }

    void TestCamera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        m_camera->key_callback(window, key, scancode, action, mods);
    }

    void TestCamera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        m_camera->mouse_callback(window, xpos, ypos);
    }
}

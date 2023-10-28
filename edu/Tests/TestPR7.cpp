#include "TestPR7.h"

namespace test {

	TestPR7::TestPR7()
	{
        VertexBufferLayout vbLayout;
        vbLayout.Push<float>(2); // 2 координаты
        vbLayout.Push<float>(2); // 2 координаты по картинке

        GLfloat square[] = {
                -0.7f,   -0.7f, 0.0f, 0.0f,
                0.0f,    0.7f, 0.0f, 1.0f,
                0.7f,    -0.7f, 1.0f, 1.0f,
        };

        auto squareBuffer = VertexBuffer(square, sizeof(square));

        m_squareVertexArray = new VertexArray();
        m_squareVertexArray->AddBuffer(squareBuffer, vbLayout);
        unsigned int squareIndices[] = {
                0, 1, 2,
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
        m_scale = 1.0f;
        m_rotation = 0.0f;

        m_shader = new Shader("../edu/res/TextureShader.vs", "../edu/res/TextureShader.fs");
        m_shader->Bind();
        m_shader->SetUniformMat4f("u_MVP", m_mvp);
        m_shader->SetUniform1i("u_Texture", 0);
        mode = true;

        m_texture = new Texture("../edu/res/capy.jpg");
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        m_texture->bind(0);
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));

        m_renderer = new Renderer();
	}

	TestPR7::~TestPR7()
	{
        delete m_squareIndexBuffer;
        delete m_shader;
        delete m_squareVertexArray;
        delete m_texture;
        delete m_renderer;
	}

	void TestPR7::OnUpdate(float deltaTime)
	{
        m_renderer->Clear();
	}

	void TestPR7::OnRender()
	{
        m_model = glm::translate(glm::mat4(1.0f), m_translation);
        m_model = glm::scale(m_model, glm::vec3(m_scale));
        m_model = glm::rotate(m_model, glm::radians(m_rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        m_mvp = m_proj * m_view * m_model;

        m_shader->Bind();
        m_shader->SetUniformMat4f("u_MVP", m_mvp);
        m_shader->SetUniform1i("u_Texture", 0);

        m_renderer->Draw(*m_squareVertexArray, *m_squareIndexBuffer, *m_shader);
	}

	void TestPR7::OnImGuiRender()
	{
        if ( ImGui::Button("mipmap mode") )
        {
            if (!mode)
            {
                GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
            }
            else
            {
                GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            }
            mode = !mode;
        }
        ImGui::SliderFloat2("model position", &m_translation.x, -1.0f, 1.0f);
        ImGui::SliderFloat("model scale", &m_scale, 0.01f, 5.0f);
        ImGui::SliderFloat("model rotation", &m_rotation, 0.01f, 180.0f);
	}

}

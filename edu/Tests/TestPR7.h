#pragma once
#include "Test.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Renderer.h"

namespace test {

    class TestPR7 : public Test
    {
	private:
		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::mat4 m_model;
		glm::mat4 m_mvp;
		glm::vec3 m_translation;
		float m_scale;
		float m_rotation;
		bool mode;

		VertexArray* m_squareVertexArray;
		IndexBuffer* m_squareIndexBuffer;
		Shader* m_shader;
		Renderer* m_renderer;
		Texture* m_texture;
	public:
		TestPR7();
		virtual ~TestPR7();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
    };

}

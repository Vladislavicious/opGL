#pragma once
#include "Test.h"

namespace test {

    class TestMovingSquare : public Test
    {
	private:
		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::mat4 m_model;
		glm::mat4 m_mvp;
		glm::vec3 m_translation;

		VertexArray* m_squareVertexArray;
		IndexBuffer* m_squareIndexBuffer;
		Shader* m_shader;
		Renderer* m_renderer;
		Texture* m_texture;
	public:
		TestMovingSquare();
		virtual ~TestMovingSquare();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
    };

}

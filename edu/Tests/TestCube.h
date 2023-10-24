#pragma once
#include "Test.h"
#include "Renderer.h"


namespace test {

    class TestCube : public Test
    {
	private:
		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::mat4 m_model;
		glm::mat4 m_mvp;
		glm::vec3 m_rotation;

		VertexArray* m_cubeVertexArray;
		IndexBuffer* m_cubeIndexBuffer;
		Shader* m_shader;
		Renderer* m_renderer;
	public:
		TestCube();
		virtual ~TestCube();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
    };

}

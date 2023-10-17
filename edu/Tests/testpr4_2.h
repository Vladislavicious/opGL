#pragma once
#include "Test.h"

namespace test {

    class TestPR4_2 : public Test
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

		float x_ortho[2];
		float y_ortho[2];
		float z_ortho[2];
		float m_translationZ = 0.0f;

		bool ortho = true;
		glm::mat4 getViewMatrix(float *x_bounds, float *y_bounds, float *z_bounds);
	public:
		TestPR4_2();
		virtual ~TestPR4_2();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
    };

}

#pragma once
#include "Test.h"
#include "myCamera.h"

namespace test {

    class TestLighting : public Test
    {
	private:
		glm::mat4 m_proj;
		glm::mat4 m_cubeModel;
		glm::mat4 m_lightModel;
		glm::vec3 m_rotation;

		glm::vec3 m_lightPos;

		VertexArray* m_cubeVertexArray;
		IndexBuffer* m_cubeIndexBuffer;
		Shader* m_cubeShader;

		VertexArray* m_lightVertexArray;
		IndexBuffer* m_lightIndexBuffer;
		Shader* m_lightShader;

		Renderer* m_renderer;

		float z_ortho[2];

		bool cursorActivated = false;
		glm::mat4 getProjectionMatrix(float near_z_bound, float far_z_bound);
	public:
		TestLighting();
		virtual ~TestLighting();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
    };

}

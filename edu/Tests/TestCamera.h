#pragma once
#include "Test.h"
#include "myCamera.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
class VertexBufferLayout;

namespace test {

    class TestCamera : public Test
    {
	private:
		glm::mat4 m_proj;
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

		bool ortho = false;
		bool cursorActivated = false;
		glm::mat4 getProjectionMatrix(float *x_bounds, float *y_bounds, float *z_bounds);

    public:
        TestCamera();
		virtual ~TestCamera();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

        void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) override;
		void mouse_callback(GLFWwindow* window, double xpos, double ypos) override;
    };

}

#pragma once
#include "Test.h"
#include "myCamera.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Renderer.h"

namespace test {

    class TestLighting : public Test
    {
	private:
		glm::mat4 m_proj;
		glm::mat4 m_cubeModel;
		glm::vec3 m_cubePositions[10];
		glm::mat4 m_lightModel;
		glm::vec3 m_lightPos;

		glm::vec3 m_pointLightColor;
		glm::vec3 m_dirLightPower;
		float m_spotLightRadius;

		bool isDirLightOn = true;
		bool isSpotLightOn = true;

		Texture* m_cubeTexture;
		Texture* m_cubeSpecTexture;
		VertexArray* m_cubeVertexArray;
		IndexBuffer* m_cubeIndexBuffer;
		Shader* m_cubeShader;

		VertexArray* m_lightVertexArray;
		IndexBuffer* m_lightIndexBuffer;
		Shader* m_lightShader;

		Renderer* m_renderer;

		float z_ortho[2];
		std::unique_ptr<myCamera> m_camera;

		bool cursorActivated = false;
		glm::mat4 getProjectionMatrix(float near_z_bound, float far_z_bound);
	public:
		TestLighting();
		virtual ~TestLighting();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) override;
		void mouse_callback(GLFWwindow* window, double xpos, double ypos) override;
    };

}

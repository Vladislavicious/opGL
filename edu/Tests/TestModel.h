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
#include "myMesh.h"
#include "myModel.h"

namespace test {

    class TestModel : public Test
    {
	private:
		glm::mat4 m_proj;
		glm::mat4 m_cubeModel;
		glm::mat4 m_lightModel;
		glm::vec3 m_lightPos;

		glm::vec3 m_pointLightColor;
		glm::vec3 m_dirLightPower;
		float m_spotLightRadius;

		bool isDirLightOn = true;
		bool isSpotLightOn = true;

		Texture* m_cubeTexture;
		Texture* m_cubeSpecTexture;
		Shader* m_cubeShader;
		myMesh* m_cubeMesh;

		myModel* m_backpack;

		VertexArray* m_lightVertexArray;
		IndexBuffer* m_lightIndexBuffer;
		Shader* m_lightShader;

		Renderer* m_renderer;

		float z_ortho[2];

		bool cursorActivated = false;
		glm::mat4 getProjectionMatrix(float near_z_bound, float far_z_bound);
	public:
		TestModel();
		virtual ~TestModel();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
    };

}

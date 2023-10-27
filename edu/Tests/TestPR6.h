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
#include "pointLight.h"

namespace test {

    class TestPR6 : public Test
    {
	private:
		glm::mat4 m_proj;

		glm::vec3 m_dirLightPower;
		glm::vec3 m_modelMovement;
		float m_spotLightRadius;

		bool isDirLightOn = true;
		bool isSpotLightOn = true;
		bool isMaterial = true;

		std::vector<std::shared_ptr<Texture>> m_textures;
		Shader* m_modelShader;
		myModel* m_myModel;

		std::vector<std::shared_ptr<PointLight>> m_pointLights;
		Renderer* m_renderer;

		float z_ortho[2];

		bool cursorActivated = false;
		glm::mat4 getProjectionMatrix(float near_z_bound, float far_z_bound);
	public:
		TestPR6();
		virtual ~TestPR6();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
    };

}

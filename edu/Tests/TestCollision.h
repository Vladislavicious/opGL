#ifndef _TEST_COLLISION_H
#define _TEST_COLLISION_H

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
#include "bBox.h"

namespace test {

    class TestCollision : public Test
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
		std::vector<std::shared_ptr<bBox>> m_bBoxes;
		Renderer* m_renderer;

		std::unique_ptr<myCamera> m_camera;
		float z_ortho[2];

		bool cursorActivated = false;
		glm::mat4 getProjectionMatrix(float near_z_bound, float far_z_bound);
	public:
		TestCollision();
		virtual ~TestCollision();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) override;
		void mouse_callback(GLFWwindow* window, double xpos, double ypos) override;
    };

}
#endif // _TEST_COLLISION_H

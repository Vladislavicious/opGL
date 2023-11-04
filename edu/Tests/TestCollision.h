#ifndef _TEST_COLLISION_H
#define _TEST_COLLISION_H
#include "src/q3.h"
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
#include "vObject.h"
#include "myLight.h"
#include "vDynamicModel.h"

namespace test {

    class TestCollision : public Test
    {
	private:
		glm::mat4 m_proj;

		glm::vec3 m_dirLightPower;
		glm::vec3 m_modelMovement;

		std::vector<std::shared_ptr<Texture>> m_textures;
		std::unique_ptr<v::DynamicModel> m_myModel;
		std::vector<std::shared_ptr<v::PointLight>> m_pointLights;
		std::vector<std::shared_ptr<v::Object>> m_bBoxes;

		std::shared_ptr<q3Scene> m_scene;

		Renderer* m_renderer;
		std::unique_ptr<v::DirLight> m_directLight;
		std::unique_ptr<v::SpotLight> m_spotLight;

		std::unique_ptr<myCamera> m_camera;
		float z_ortho[2];

		bool cursorActivated = false;
		bool bBoxesVisible = true;
		glm::mat4 getProjectionMatrix(float near_z_bound, float far_z_bound);
		void addBody();
	public:
		TestCollision();
		virtual ~TestCollision();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) override;
		void mouse_callback(GLFWwindow* window, double xpos, double ypos) override;
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) override;
    };

}
#endif // _TEST_COLLISION_H

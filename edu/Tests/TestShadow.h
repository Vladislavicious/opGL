#ifndef _TEST_SHADOW_H
#define _TEST_SHADOW_H
#include "Test.h"
#include "Shader.h"
#include "Texture.h"
#include "pointLight.h"
#include "myLight.h"
#include "vPlayer.h"

namespace test {

    class TestShadow : public Test
    {
	private:
		glm::mat4 m_proj;

		glm::vec3 m_dirLightPower;
		glm::vec3 m_modelMovement;

		std::vector<std::shared_ptr<Texture>> m_textures;
		std::shared_ptr<v::Player> m_Player;

		std::vector<std::shared_ptr<v::DynamicModel>> m_models;
		std::vector<std::shared_ptr<v::PointLight>> m_pointLights;

		float time_elapsed;

		Renderer* m_renderer;
		std::unique_ptr<v::DirLight> m_directLight;
		std::unique_ptr<v::SpotLight> m_spotLight;

		float z_ortho[2];

		bool cursorActivated = false;
		bool bBoxesVisible = true;
	public:
		TestShadow();
		virtual ~TestShadow();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) override;
		void mouse_callback(GLFWwindow* window, double xpos, double ypos) override;
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) override;
    };

}
#endif // _TEST_SHADOW_H

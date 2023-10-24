#pragma once

#include <vector>
#include <functional>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace test {

	class Test
	{

	public:
		static GLFWwindow* window;
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test
	{
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	public:
		TestMenu(Test*& currentTestPointer);

		virtual void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;
			m_Tests.push_back(std::make_pair(  name, []() { return new T(); }));
		}

		void BuildAll();
	};

}

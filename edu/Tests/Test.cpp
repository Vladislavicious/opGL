#include "Test.h"

namespace test {

	GLFWwindow* Test::window = nullptr;

	TestMenu::TestMenu(Test*& currentTestPointer) :
		m_CurrentTest(currentTestPointer)
	{
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second();
			}
		}
	}

    void TestMenu::BuildAll()
    {
		for (auto& test : m_Tests)
		{
			std::cout << "Building " << test.first.c_str() << std::endl;
			auto temp = test.second();
			std::cout << "Build completed\n";
			delete temp;
		}
    }
}

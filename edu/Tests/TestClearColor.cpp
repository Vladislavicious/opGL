#include "TestClearColor.h"

namespace test {


	TestClearColor::TestClearColor::TestClearColor():
		m_ClearColor{0.3f, 0.5f, 0.1f, 1.0f}
	{
	}

	TestClearColor::TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::TestClearColor::OnUpdate(float deltaTime)
	{
	}

	void TestClearColor::TestClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit3("Clear Color", m_ClearColor);
	}

}
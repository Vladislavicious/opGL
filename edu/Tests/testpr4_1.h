#pragma once
#include "Test.h"

namespace test {

    class TestPR4_1: public Test
    {
	private:
		bool enabled = false;
		VertexArray* m_squareVertexArray;
		VertexArray* m_square1VertexArray;
		VertexArray* m_triangleVertexArray;
		IndexBuffer* m_squareIndexBuffer;
		IndexBuffer* m_triangleIndexBuffer;
		Shader* m_shader;
		Renderer* m_renderer;
	public:
		TestPR4_1();
		virtual ~TestPR4_1();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;
    };

}

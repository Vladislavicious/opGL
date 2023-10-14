#include "Renderer.h"

VertexArray::VertexArray() : vertexArrayID(0)
{
	GLCall(glGenVertexArrays(1, &vertexArrayID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &vertexArrayID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout)
{
	this->Bind();

	vb.Bind();

	const auto& elements = vbLayout.GetLayoutElements();

	unsigned int offset = 0;

	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];


		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, vbLayout.GetStride(), (void*)offset));
		GLCall(glEnableVertexAttribArray(i));

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);

	}

}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(vertexArrayID));
}

void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}

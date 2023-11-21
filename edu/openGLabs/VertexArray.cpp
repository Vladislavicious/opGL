#include "VertexArray.h"

VertexArray::VertexArray() :
	vertexArrayID(0), layout(), buffer()
{
	GLCall(glGenVertexArrays(1, &vertexArrayID));
}

VertexArray::VertexArray(std::vector<Vertex>& vertices) :
	vertexArrayID(0), layout(getLayout()), buffer(new VertexBuffer(vertices))
{
	GLCall(glGenVertexArrays(1, &vertexArrayID));
    AddBuffer(*buffer, layout);
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &vertexArrayID));
	delete buffer;
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout)
{
	this->Bind();
	if (buffer == nullptr)
		buffer = new VertexBuffer(vb);
	layout = VertexBufferLayout(vbLayout);
	buffer->Bind();

	const auto& elements = layout.GetLayoutElements();

	unsigned int offset = 0;

	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];


		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (void*)offset));
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

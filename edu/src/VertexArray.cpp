#include "VertexArray.h"

VertexArray::VertexArray() :
	vertexArrayID(0), layout(nullptr), buffer(nullptr)
{
	GLCall(glGenVertexArrays(1, &vertexArrayID));
}

VertexArray::VertexArray(std::vector<Vertex>& vertices) :
	vertexArrayID(0), layout(new VertexBufferLayout()), buffer(new VertexBuffer(vertices))
{
	GLCall(glGenVertexArrays(1, &vertexArrayID));

    layout->Push<float>(3); // 3 координаты
    layout->Push<float>(3); // 3 нормали
    layout->Push<float>(2); // 2 текстурных координаты

    AddBuffer(*buffer, *layout);
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &vertexArrayID));
	if (buffer != nullptr)
		delete buffer;
	if (layout != nullptr)
		delete layout;
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout)
{
	this->Bind();
	if (buffer == nullptr)
		buffer = new VertexBuffer(vb);
	if (layout == nullptr)
		layout = new VertexBufferLayout(vbLayout);
	buffer->Bind();

	const auto& elements = layout->GetLayoutElements();

	unsigned int offset = 0;

	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];


		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout->GetStride(), (void*)offset));
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

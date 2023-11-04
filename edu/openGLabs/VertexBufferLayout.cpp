#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
{
	stride = 0;
}

unsigned int VertexBufferElement::GetSizeOfType(unsigned int type)
{
	switch (type)
	{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
	}

	ASSERT(false);	return 0;
}


template<>
void VertexBufferLayout::Push<float>(unsigned int count)
{
	VertexBufferElement temp = { GL_FLOAT, count, GL_FALSE };

	layoutElements.push_back(temp);

	stride += VertexBufferElement::GetSizeOfType(temp.type) * count;
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
	VertexBufferElement temp = { GL_UNSIGNED_INT, count, GL_FALSE };

	layoutElements.push_back(temp);

	stride += VertexBufferElement::GetSizeOfType(temp.type) * count;
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
	VertexBufferElement temp = { GL_UNSIGNED_BYTE, count, GL_TRUE };

	layoutElements.push_back(temp);

	stride += VertexBufferElement::GetSizeOfType(temp.type) * count;
}

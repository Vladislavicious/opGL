#ifndef VERTEXBUFFERLAYOUT_H_
#define VERTEXBUFFERLAYOUT_H_


#include <vector>

#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type);
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> layoutElements;
	unsigned int stride;
public:
	VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count)
	{
	}
	template<>
	void Push< float >(unsigned int count)
	{
		VertexBufferElement temp = { GL_FLOAT, count, GL_FALSE };

		layoutElements.push_back(temp);

		stride += VertexBufferElement::GetSizeOfType(temp.type) * count;
	}

	template<>
	void Push< unsigned int >(unsigned int count)
	{
		VertexBufferElement temp = { GL_UNSIGNED_INT, count, GL_FALSE };

		layoutElements.push_back(temp);

		stride += VertexBufferElement::GetSizeOfType(temp.type) * count;
	}

	template<>
	void Push< unsigned char >(unsigned int count)
	{
		VertexBufferElement temp = { GL_UNSIGNED_BYTE, count, GL_TRUE };

		layoutElements.push_back(temp);

		stride += VertexBufferElement::GetSizeOfType(temp.type) * count;
	}

	inline unsigned int GetStride() const { return stride; }

	inline const std::vector<VertexBufferElement> GetLayoutElements() const& { return layoutElements; }
};


#endif // !VERTEXBUFFERLAYOUT_H_

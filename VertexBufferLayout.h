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

	inline unsigned int GetStride() const { return stride; }

	inline const std::vector<VertexBufferElement> GetLayoutElements() const& { return layoutElements; }
};


#endif // !VERTEXBUFFERLAYOUT_H_

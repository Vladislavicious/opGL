#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_

#include "Renderer.h"
#include "VertexBufferLayout.h"
class VertexBufferLayout;
#include "VertexBuffer.h"
class VertexBuffer;
class VertexArray
{
private:
	unsigned int vertexArrayID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout);

	void Bind() const;
	void UnBind() const;
};


#endif // !VERTEXARRAY_H_

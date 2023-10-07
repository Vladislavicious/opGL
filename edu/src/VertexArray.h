#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_

#include "VertexBuffer.h"

class VertexBufferLayout;

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

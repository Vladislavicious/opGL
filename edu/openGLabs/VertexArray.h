#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_

#include "Renderer.h"
#include "VertexBufferLayout.h"
class VertexBufferLayout;
#include "VertexBuffer.h"
class VertexBuffer;
#include "myVertex.h"

class VertexArray
{
private:
	unsigned int vertexArrayID;
	VertexBufferLayout layout;
	VertexBuffer* buffer;
public:
	VertexArray();
	explicit VertexArray(std::vector<Vertex>& vertices);
	VertexArray(const VertexArray& other) = delete;
	VertexArray(VertexArray&& other) noexcept: vertexArrayID(other.vertexArrayID),
												layout(std::move(other.layout)), buffer(std::move(other.buffer)) {};
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout);

	VertexArray operator = (const VertexArray& a) = delete;

	void Bind() const;
	void UnBind() const;
};


#endif // !VERTEXARRAY_H_

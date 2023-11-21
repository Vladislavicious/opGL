#ifndef VERTEXBUFFER_H_
#define VERTEXBUFFER_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW
#include "Renderer.h"
#include "myVertex.h"
struct Vertex;

class VertexBuffer
{
private:
	unsigned int bufferID;
public:
	VertexBuffer(const void* data, unsigned int sizeInBites);
	explicit VertexBuffer(std::vector<Vertex> &vertices);
	VertexBuffer(): bufferID(0) {};
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};


#endif // !VERTEXBUFFER_H_

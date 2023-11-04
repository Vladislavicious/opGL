#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int sizeInBites)
{
    GLCall(glGenBuffers(1, &bufferID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeInBites, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(std::vector<Vertex> &vertices)
{
    GLCall(glGenBuffers(1, &bufferID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
    GLCall(unsigned int sizeInBites = vertices.size() * sizeof(Vertex));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeInBites, &vertices[0], GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &bufferID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
}

void VertexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

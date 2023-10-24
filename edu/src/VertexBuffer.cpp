#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int sizeInBites)
{
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeInBites, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(std::vector<Vertex> vertices)
{
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    unsigned int sizeInBites = vertices.size() * sizeof(Vertex);
    glBufferData(GL_ARRAY_BUFFER, sizeInBites, &vertices[0], GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &bufferID));
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void VertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

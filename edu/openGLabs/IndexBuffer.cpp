#include "IndexBuffer.h"
#include "Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int countElements):
    indexBufferID{0}, indexCount{countElements}
{
    GLCall(glGenBuffers(1, &indexBufferID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, countElements * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data):
    indexBufferID{0}, indexCount{static_cast<unsigned int>(data.size())}
{
    GLCall(glGenBuffers(1, &indexBufferID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), &data[0], GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &indexBufferID));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID));
}

void IndexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

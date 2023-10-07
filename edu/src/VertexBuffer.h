#ifndef VERTEXBUFFER_H_
#define VERTEXBUFFER_H_


class VertexBuffer
{
private:
	unsigned int bufferID;
public:
	VertexBuffer(const void* data, unsigned int sizeInBites);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};


#endif // !VERTEXBUFFER_H_

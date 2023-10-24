#ifndef INDEXBUFFER_H_
#define INDEXBUFFER_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW
#include <vector>
class IndexBuffer
{
private:
	unsigned int indexBufferID;
	unsigned int indexCount;
public:
	IndexBuffer(const unsigned int* data, unsigned int countElements);
	IndexBuffer(std::vector<unsigned int> data);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return indexCount; }
};


#endif // !INDEXBUFFER_H_

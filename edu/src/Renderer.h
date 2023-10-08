#include <stdio.h> //Для простого консольного вывода ошибок
#include <iostream>
#include <signal.h>

#include <GL/glew.h> // подключение GLEW
#include <GLFW/glfw3.h> // подключение GLFW
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"


#ifndef RENDERER_H_
#define RENDERER_H_

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:

    void Clear() const;

    void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, GLenum mode) const;
};

#endif //RENDERER_H_

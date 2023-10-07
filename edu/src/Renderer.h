#include <GL/glew.h> // подключение GLEW
#include <GLFW/glfw3.h> // подключение GLFW
#include <stdio.h> //Для простого консольного вывода ошибок
#include <iostream>
#include <signal.h>
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

#ifndef RENDERER_H_
#define RENDERER_H_

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:

    void Clear() const;

    void Draw(const VertexArray& vertexArray, const Shader& shader, int count) const;
};

#endif //RENDERER_H_

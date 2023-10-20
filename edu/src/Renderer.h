#include <stdio.h> //Для простого консольного вывода ошибок
#include <iostream>
#include <signal.h>


#include <glad/glad.h>
#include <GLFW/glfw3.h> // подключение GLFW
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#ifndef RENDERER_H_
#define RENDERER_H_

#ifdef SIGTRAP
#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#else
#define ASSERT(x) if(!(x)) raise(SIGABRT);
#endif // SIGTRAP
#define GLCall(x) GLClearError();x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


extern float deltaTime;	// Time between current frame and last frame
extern float lastFrame; // Time of last frame

extern int WinWidth;
extern int WinHeight;

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:

    void Clear() const;

    void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, GLenum mode = GL_TRIANGLES) const;
};

#endif //RENDERER_H_

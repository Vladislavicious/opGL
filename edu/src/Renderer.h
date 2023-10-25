#ifndef RENDERER_H_
#define RENDERER_H_

#include <signal.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "myMesh.h"
#include "myModel.h"
class myMesh;
class myModel;
class VertexArray;
#ifdef SIGTRAP
#define ASSERT(x) if(!(x)) raise(SIGTRAP);
#else
#define ASSERT(x) if(!(x)) raise(SIGABRT);
#endif // SIGTRAP
#define GLCall(x) GLClearError(__FILE__, __LINE__);x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


extern float deltaTime;	// Time between current frame and last frame
extern float lastFrame; // Time of last frame

extern int WinWidth;
extern int WinHeight;

void GLClearError(const char *file, int line);

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:

    void Clear() const;

    void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
    void Draw(const myMesh &mesh, Shader &shader);
    void Draw(const myModel &model, Shader &shader);
};

#endif //RENDERER_H_

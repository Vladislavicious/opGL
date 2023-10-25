#ifndef _MY_VERTEX_H
#define _MY_VERTEX_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <vector>
#include "VertexBufferLayout.h"
class VertexBufferLayout;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

};

std::vector<Vertex> getVertices(float* data, unsigned int count);
VertexBufferLayout* getLayout();

#endif // _MY_VERTEX_H

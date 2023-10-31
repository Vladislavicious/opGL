#ifndef _MY_VERTEX_H
#define _MY_VERTEX_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <vector>
#include "VertexBufferLayout.h"
class VertexBufferLayout;
#include "pVector.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

};

std::vector<Vertex> getVertices(float* data, unsigned int count);
VertexBufferLayout* getLayout();
std::vector<FlatVector> getFlatVectors(std::vector<Vertex> vertices);

#endif // _MY_VERTEX_H

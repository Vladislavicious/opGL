#include "myVertex.h"

std::vector<Vertex> getVertices(float* data, unsigned int count)
{
    std::vector<Vertex> vertices;
    vertices.reserve(count);
    for (int i = 0; i < count * sizeof(Vertex) / sizeof(float); i+=8)
    {
        Vertex temp;
        temp.Position = { glm::vec3(data[i], data[i+1], data[i+2]) };
        temp.Normal = { glm::vec3(data[i+3], data[i+4], data[i+5]) };
        temp.TexCoords = { glm::vec2(data[i+6], data[i+7]) };
        vertices.push_back(temp);
    }
    return vertices;
}

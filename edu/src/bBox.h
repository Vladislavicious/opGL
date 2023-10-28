#ifndef _B_BOX_H
#define _B_BOX_H

#include "Shader.h"
#include "myModel.h"


class bBox
{
private:
    glm::vec3 m_pos;
    glm::vec3 m_size;

    Shader* m_shader;
    myModel* m_model;
public:
    bBox(glm::vec3 position, glm::vec3 size, const std::string& vsShaderPath,
         const std::string& fsShaderPath);
    ~bBox();
    void ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix) const;
    glm::vec3& getPos() { return m_pos; }
    const myModel& getModel() { return *m_model; }
    Shader& getShader() { return *m_shader; }
};

#endif // _B_BOX_H

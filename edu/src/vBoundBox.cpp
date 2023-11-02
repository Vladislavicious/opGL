#include "vBoundBox.h"
#include <glm/gtx/quaternion.hpp>

glm::mat4 rotateMat4(const q3Mat3& rotationMatrix);

namespace v
{
    boundBox::boundBox(glm::vec3 position, glm::vec3 size, const std::string& vsShaderPath,
                    const std::string& fsShaderPath, std::shared_ptr<Renderer> renderer,
                    std::shared_ptr<q3Scene> scene, bool isStatic):
                Object(position, size, "../edu/res/cube/cube.obj", vsShaderPath, fsShaderPath, renderer)
    {
        bodyDef.bodyType = eDynamicBody;
        if (isStatic)
            bodyDef.bodyType = eStaticBody;
        bodyDef.position = q3Vec3(position.x, position.y, position.z);
        body = scene->CreateBody( bodyDef );
        q3Transform localSpace; // Contains position and orientation, see q3Transform.h for details
        q3Identity( localSpace ); // Specify the origin, and identity orientation
        // Create a box at the origin with width, height, depth = (1.0, 1.0, 1.0)
        // and add it to a rigid body. The transform is defined relative to the owning body
        q3BoxDef boxDef;
        boxDef.Set( localSpace, q3Vec3( 2 * size.x, 2 * size.y, 2 * size.z ) );
        boxDef.SetRestitution( 0 );
        body->AddBox( boxDef );
    }

    void boundBox::ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix)
    {
        auto vec = body->GetTransform();
        setPos(vec.position);

        auto model = glm::translate(glm::mat4(1.0f), m_pos);
        model = glm::scale(model, glm::vec3(m_size));
        model = model * rotateMat4(vec.rotation);
        m_shader->Bind();

        m_shader->SetUniformMat4f("view", viewMatrix);
        m_shader->SetUniformMat4f("projection", projMatrix);
        m_shader->SetUniform3f("colour", glm::vec3(0.6f));
        m_shader->SetUniformMat4f("model", model);
    }
}

glm::mat4 rotateMat4(const q3Mat3& rotationMatrix)
{
    glm::mat4 modelMatrix(1.0f); // Создаем единичную матрицу 4x4

    // Копируем матрицу поворота 3x3 в верхний левый угол матрицы 4x4
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            modelMatrix[i][j] = rotationMatrix[i][j];
        }
    }
    return modelMatrix;
}
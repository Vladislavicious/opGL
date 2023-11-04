#include "vBoundBox.h"
#include <glm/gtx/quaternion.hpp>

glm::mat4 rotateMat4(const q3Mat3& rotationMatrix);

namespace v
{
    glm::mat4 boundBox::createModelMatrix()
    {
        auto vec = body->GetTransform();
        setPos(vec.position);

        auto model = glm::translate(glm::mat4(1.0f), m_pos);
        model = model * rotateMat4(vec.rotation);
        model = glm::scale(model, glm::vec3(m_size));
        return model;
    }

    glm::mat4 boundBox::getNonScaledModelMatrix()
    {
        auto vec = body->GetTransform();
        setPos(vec.position);

        auto model = glm::translate(glm::mat4(1.0f), m_pos);
        model = model * rotateMat4(vec.rotation);
        return model;
    }

    boundBox::boundBox(glm::vec3 position, glm::vec3 size,
                       std::shared_ptr<q3Scene> scene, bool isStatic, bool lockAxisX,
                       bool lockAxisY, bool lockAxisZ) :
                       Object(position, size, "../edu/res/cube/cube.obj", "../edu/res/cube/bBoxShader.vs",
                                                                               "../edu/res/cube/bBoxShader.fs")
    {
        q3BodyDef bodyDef;
        bodyDef.bodyType = eDynamicBody;
        if (isStatic)
            bodyDef.bodyType = eStaticBody;
        bodyDef.position = q3Vec3(position.x, position.y, position.z);
        bodyDef.lockAxisX = lockAxisX;
        bodyDef.lockAxisY = lockAxisY;
        bodyDef.lockAxisZ = lockAxisZ;
        body = scene->CreateBody( bodyDef );
        q3Transform localSpace;
        q3Identity( localSpace );
        q3BoxDef boxDef;
        boxDef.Set( localSpace, q3Vec3( 2 * size.x, 2 * size.y, 2 * size.z ) );
        boxDef.SetRestitution( 0 );
        body->AddBox( boxDef );
    }

    void boundBox::ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix)
    {
        Object::ToDrawShader(viewMatrix, projMatrix);
        m_shader->SetUniform3f("colour", glm::vec3(0.6f));
    }

    void boundBox::rotate(q3Vec3 axis, float angle)
    {
        auto temp = body->GetTransform();
        body->SetTransform(temp.position, axis, glm::radians(angle));
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

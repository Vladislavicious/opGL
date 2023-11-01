#include "vMovingObject.h"

namespace v
{
    boundBox::boundBox(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath,
                std::shared_ptr<Renderer> renderer, std::shared_ptr<q3Scene> scene,
                bool isStatic):
                Object(position, size, filePath, vsShaderPath, fsShaderPath, renderer)
    {
        bodyDef.bodyType = eDynamicBody;
        if (isStatic)
            bodyDef.bodyType = eStaticBody;
        bodyDef.gravityScale = 0.05;
        bodyDef.position = q3Vec3(position.x, position.y, position.z);
        body = scene->CreateBody( bodyDef );
        q3Transform localSpace; // Contains position and orientation, see q3Transform.h for details
        q3Identity( localSpace ); // Specify the origin, and identity orientation
        // Create a box at the origin with width, height, depth = (1.0, 1.0, 1.0)
        // and add it to a rigid body. The transform is defined relative to the owning body
        q3BoxDef boxDef;
        boxDef.Set( localSpace, q3Vec3( size.x, size.y, size.z ) );
        boxDef.SetRestitution( 0 );
        body->AddBox( boxDef );
    }

    void boundBox::ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix)
    {
        auto vec = body->GetLinearVelocity();
        addVelVec(vec.x, vec.y, vec.z);
        std::cout << vec.y << std::endl;
        std::cout << bodyDef.position.y;
        vec = body->GetAngularVelocity();
        addRotation(vec.x, vec.y, vec.z);

        Object::ToDrawShader(viewMatrix, projMatrix);
    }
}

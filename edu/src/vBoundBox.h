#ifndef _MOVING_OBJ_H
#define _MOVING_OBJ_H

#include "src/q3.h"
#include "vObject.h"
#include <memory>
namespace v
{
    class boundBox : public Object
    {
    private:
        q3Body* body;
    protected:
        glm::mat4 createModelMatrix() override;
        void rotate(q3Vec3 axis, float angle);
    public:
        glm::mat4 getNonScaledModelMatrix();
        boundBox(glm::vec3 position, glm::vec3 size,
                       std::shared_ptr<q3Scene> scene, bool isStatic = false, bool lockAxisX = false,
                       bool lockAxisY = false, bool lockAxisZ = false);

        void ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix)  override;
        void setPos(q3Vec3 position) { Object::setPos(glm::vec3(position.x, position.y, position.z)); }
        void rotateX(float angle) { rotate(q3Vec3(1.0f, 0.0f, 0.0f), angle); };
        void rotateY(float angle) { rotate(q3Vec3(0.0f, 1.0f, 0.0f), angle); };
        void rotateZ(float angle) { rotate(q3Vec3(0.0f, 0.0f, 1.0f), angle); };
        virtual void applyVelocity(q3Vec3 force) { body->SetLinearVelocity(force); }
        q3Vec3 getVelocity() { return body->GetLinearVelocity(); }
    };
}

#endif // _MOVING_OBJ_H

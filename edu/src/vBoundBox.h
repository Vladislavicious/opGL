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
        q3BodyDef bodyDef;
        q3Body* body;
    protected:
        glm::mat4 createModelMatrix() override;
    public:
        glm::mat4 getNonScaledModelMatrix();
        boundBox(glm::vec3 position, glm::vec3 size,
                std::shared_ptr<q3Scene> scene, bool isStatic = false);

        void ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix)  override;
        void setPos(q3Vec3 position) { Object::setPos(glm::vec3(position.x, position.y, position.z)); }
    };
}

#endif // _MOVING_OBJ_H

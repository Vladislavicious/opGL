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
    public:
        boundBox(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath,
                std::shared_ptr<Renderer> renderer, std::shared_ptr<q3Scene> scene,
                bool isStatic = false);

        void ToDrawShader(glm::mat4& viewMatrix, glm::mat4& projMatrix)  override;
        void setPos(q3Vec3 position) { Object::setPos(glm::vec3(position.x, position.y, position.z)); }
    };
}

#endif // _MOVING_OBJ_H

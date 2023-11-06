#ifndef _B_BOXED_MODEL_H
#define _B_BOXED_MODEL_H

#include "Shader.h"
#include "vObject.h"
#include "vBoundBox.h"

namespace v
{
    class DynamicModel: public Object
    {
    protected:
        std::shared_ptr<v::boundBox> m_bBox;
        glm::mat4 createModelMatrix() override;
    public:
        DynamicModel(glm::vec3 position, glm::vec3 size, const std::string& filePath,
                const std::string& vsShaderPath, const std::string& fsShaderPath);
        void addBoundBox(glm::vec3 relatedPosition, glm::vec3 size, bool isStatic,
                        bool lockAxisX = false, bool lockAxisY = false, bool lockAxisZ = false);
        void deleteBoundBox();
        virtual void applyVelocity(q3Vec3 force) { m_bBox->applyVelocity(force); }
        q3Vec3 getVelocity() { return m_bBox->getVelocity(); }
    };
}

#endif // _B_BOXED_MODEL_H

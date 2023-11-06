#ifndef _V_RAYCAST_H
#define _V_RAYCAST_H
#include "src/q3.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
namespace v
{

    class Raycast : public q3QueryCallback
    {
    private:
    public:
        q3RaycastData data;
        r32 tfinal;
        q3Vec3 nfinal;
        q3Body *impactBody;
        bool active;

        Raycast();
        ~Raycast();

        bool ReportShape( q3Box *shape ) override;

        void Cast( const q3Vec3& fromVec, const q3Vec3& dirVec );


        void Activate() { active = true; }
        void DeActivate() { active = false; }
    };

};
#endif // _V_RAYCAST_H

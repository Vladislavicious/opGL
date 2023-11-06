#include "vRaycast.h"

namespace v
{
    Raycast::Raycast():
        active(false)
    {
    }

    Raycast::~Raycast()
    {
    }

    bool Raycast::ReportShape( q3Box *shape )
    {
        if ( data.toi < tfinal )
        {
            tfinal = data.toi;
            nfinal = data.normal;
            impactBody = shape->body;
        }
        data.toi = tfinal;
        return true;
    }

    void Raycast::Cast( const q3Vec3& fromVec, const q3Vec3& dirVec )
    {
        data.start = fromVec;
        data.dir = q3Normalize( dirVec );
        data.t = r32( 10000.0 );
        tfinal = FLT_MAX;
        data.toi = data.t;
        impactBody = NULL;
    }
}

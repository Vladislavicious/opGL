#ifndef _P_AABB_H
#define _P_AABB_H

#include "pVector.h"
struct FlatAABB
{
    FlatVector Min;
    FlatVector Max;

    FlatAABB() { this->Min = this->Max = FlatVector::Zero(); }

    FlatAABB(FlatVector min, FlatVector max)
    {
        this->Min = min;
        this->Max = max;
    }

    FlatAABB(float minX, float minY, float maxX, float maxY)
    {
        this->Min = FlatVector(minX, minY);
        this->Max = FlatVector(maxX, maxY);
    }
};

#endif // _P_AABB_H

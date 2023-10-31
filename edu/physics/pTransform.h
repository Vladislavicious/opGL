#ifndef _P_TRANSFORM_H
#define _P_TRANSFORM_H
#include "math.h"

struct FlatTransform
{
    static FlatTransform Zero() { return FlatTransform(0.0f, 0.0f, 0.0f); }

    float PositionX;
    float PositionY;
    float Sin;
    float Cos;

    FlatTransform(): PositionX(0.0f), PositionY(0.0f), Sin(0.0f), Cos(0.0f) {}

    FlatTransform(float x, float y, float angle)
    {
        this->PositionX = x;
        this->PositionY = y;
        this->Sin = sin(angle);
        this->Cos = cos(angle);
    };
};

#endif // _P_TRANSFORM_H

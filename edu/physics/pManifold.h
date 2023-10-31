#ifndef _P_MANIFOLD_H
#define _P_MANIFOLD_H
class FlatBody;
#include "pBody.h"
#include "pVector.h"
struct FlatManifold
{
    FlatBody& BodyA;
    FlatBody& BodyB;
    FlatVector Normal;
    float Depth;
    FlatVector Contact1;
    FlatVector Contact2;
    int ContactCount;

    FlatManifold(
        FlatBody& bodyA, FlatBody& bodyB,
        FlatVector normal, float depth,
        FlatVector contact1, FlatVector contact2, int contactCount):
        BodyA(bodyA), BodyB(bodyB), Normal(normal), Depth(depth),
        Contact1(contact1), Contact2(contact2), ContactCount(contactCount)
    {
    }
};

#endif // _P_MANIFOLD_H

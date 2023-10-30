#ifndef _P_COLLISIONS_H
#define _P_COLLISIONS_H
#include "pBody.h"
#include <tuple>
#include <vector>

struct FlatManifold
{
    FlatBody BodyA;
    FlatBody BodyB;
    FlatVector Normal;
    float Depth;
    FlatVector Contact1;
    FlatVector Contact2;
    int ContactCount;

    FlatManifold(
        FlatBody bodyA, FlatBody bodyB,
        FlatVector normal, float depth,
        FlatVector contact1, FlatVector contact2, int contactCount):
        BodyA(bodyA), BodyB(bodyB), Normal(normal), Depth(depth),
        Contact1(contact1), Contact2(contact2), ContactCount(contactCount)
    {
    }
};



static class Collisions
{
private:
    static std::tuple<FlatVector, FlatVector, int> FindPolygonsContactPoints(
        std::vector<FlatVector> verticesA, std::vector<FlatVector> verticesB,
        FlatVector contact1, FlatVector contact2, int contactCount);

    static FlatVector FindCirclePolygonContactPoint(
        FlatVector circleCenter, float circleRadius,
        FlatVector polygonCenter, std::vector<FlatVector> polygonVertices,
        FlatVector cp);

    static FlatVector FindCirclesContactPoint(FlatVector centerA, float radiusA,
    FlatVector centerB, FlatVector cp);

    static int FindClosestPointOnPolygon(FlatVector circleCenter, std::vector<FlatVector> vertices);


    static std::tuple<float, float> ProjectCircle(FlatVector center, float radius,
                        FlatVector axis, float min, float max);

    static std::tuple<float, float> ProjectVertices(std::vector<FlatVector> vertices, FlatVector axis,
                                        float min, float max);

public:

    static std::tuple<float, FlatVector> PointSegmentDistance(FlatVector p, FlatVector a, FlatVector b,
                                float distanceSquared, FlatVector cp);

    static bool IntersectAABBs(FlatAABB a, FlatAABB b);

    static std::tuple<FlatVector, FlatVector, int> FindContactPoints(
        FlatBody bodyA, FlatBody bodyB, FlatVector contact1,
        FlatVector contact2, int contactCount);

    static std::tuple<bool, FlatVector, float> Collisions::Collide(FlatBody bodyA, FlatBody bodyB,
                                                    FlatVector normal, float depth);

    static std::tuple<bool, FlatVector, float> IntersectCirclePolygon(FlatVector circleCenter, float circleRadius,
                                                FlatVector polygonCenter, std::vector<FlatVector> vertices,
                                                FlatVector normal, float depth);

    static std::tuple<bool, FlatVector, float> IntersectPolygons(FlatVector centerA, std::vector<FlatVector> verticesA, FlatVector centerB,
                                        std::vector<FlatVector> verticesB, FlatVector normal, float depth);

    static std::tuple<bool, FlatVector, float> IntersectCircles(
        FlatVector centerA, float radiusA,
        FlatVector centerB, float radiusB,
        FlatVector normal, float depth);

}
#endif // _P_COLLISIONS_H

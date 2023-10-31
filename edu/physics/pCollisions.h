#ifndef _P_COLLISIONS_H
#define _P_COLLISIONS_H
#include <tuple>
#include <vector>
#include "pManifold.h"
#include "pAABB.h"
#include "pBody.h"
class FlatBody;

class Collisions
{
private:
    static std::tuple<FlatVector, FlatVector, int> FindPolygonsContactPoints(
        std::vector<FlatVector> verticesA, std::vector<FlatVector> verticesB);


    static int FindClosestPointOnPolygon(FlatVector circleCenter, std::vector<FlatVector> vertices);

    static std::tuple<float, float> ProjectVertices(std::vector<FlatVector> vertices, FlatVector axis);

public:

    static std::tuple<float, FlatVector> PointSegmentDistance(FlatVector p, FlatVector a, FlatVector b);

    static bool IntersectAABBs(FlatAABB a, FlatAABB b);

    static std::tuple<FlatVector, FlatVector, int> FindContactPoints(
        FlatBody bodyA, FlatBody bodyB);

    static std::tuple<bool, FlatVector, float> Collide(FlatBody bodyA, FlatBody bodyB);


    static std::tuple<bool, FlatVector, float> IntersectPolygons(FlatVector centerA, std::vector<FlatVector> verticesA, FlatVector centerB,
                                        std::vector<FlatVector> verticesB);
};

#endif // _P_COLLISIONS_H

#include "pCollisions.h"

#ifndef MIN
#define MIN(a, b) a > b?b:a
#endif
std::tuple<float, FlatVector> Collisions::PointSegmentDistance(FlatVector p, FlatVector a, FlatVector b)
{
    // Возвращает distanceSquared, cp
    float distanceSquared;
    FlatVector cp;

    FlatVector ab = b - a;
    FlatVector ap = p - a;

    float proj = FlatMath::Dot(ap, ab);
    float abLenSq = FlatMath::LengthSquared(ab);
    float d = proj / abLenSq;

    if(d <= 0.0f)
    {
        cp = a;
    }
    else if(d >= 1.0f)
    {
        cp = b;
    }
    else
    {
        cp = a + ab * d;
    }

    distanceSquared = FlatMath::DistanceSquared(p, cp);
    return {distanceSquared, cp};
}

bool Collisions::IntersectAABBs(FlatAABB a, FlatAABB b)
{
    if(a.Max.X <= b.Min.X || b.Max.X <= a.Min.X ||
        a.Max.Y <= b.Min.Y || b.Max.Y <= a.Min.Y)
    {
        return false;
    }

    return true;
}

std::tuple<FlatVector, FlatVector, int> Collisions::FindContactPoints(
        FlatBody bodyA, FlatBody bodyB)
{
    // Возвращает contact1, contact2, contactCount
    FlatVector contact1 = FlatVector::Zero();
    FlatVector contact2 = FlatVector::Zero();
    int contactCount = 0;

    ShapeType shapeTypeA = bodyA.shapeType;
    ShapeType shapeTypeB = bodyB.shapeType;

    if (shapeTypeA == ShapeType::Box)
    {
        if (shapeTypeB == ShapeType::Box)
        {
            auto res = Collisions::FindPolygonsContactPoints(bodyA.GetTransformedVertices(),
                                                            bodyB.GetTransformedVertices());
            contact1 = std::get<0>(res);
            contact2 = std::get<1>(res);
            contactCount = std::get<2>(res);
        }
        else if (shapeTypeB == ShapeType::Circle)
        {
            std::cout << "Circles aren't supported yet\n";
        }
    }
    else if (shapeTypeA == ShapeType::Circle)
    {
        std::cout << "Circles aren't supported yet\n";
    }
    return { contact1, contact2, contactCount};
}
std::tuple<FlatVector, FlatVector, int> Collisions::FindPolygonsContactPoints(
        std::vector<FlatVector> verticesA, std::vector<FlatVector> verticesB)
{
    FlatVector contact1 = FlatVector::Zero();
    FlatVector contact2 = FlatVector::Zero();
    int contactCount = 0;

    float minDistSq = 3.402823466e+38F;

    for(int i = 0; i < verticesA.size(); i++)
    {
        FlatVector p = verticesA[i];

        for(int j = 0; j < verticesB.size(); j++)
        {
            FlatVector va = verticesB[j];
            FlatVector vb = verticesB[(j + 1) % verticesB.size()];
            auto result = Collisions::PointSegmentDistance(p, va, vb);
            float distSq = std::get<0>(result);
            FlatVector cp = std::get<1>(result);

            if(FlatMath::NearlyEqual(distSq, minDistSq))
            {
                if (!FlatMath::NearlyEqual(cp, contact1))
                {
                    contact2 = cp;
                    contactCount = 2;
                }
            }
            else if(distSq < minDistSq)
            {
                minDistSq = distSq;
                contactCount = 1;
                contact1 = cp;
            }
        }
    }

    for (int i = 0; i < verticesB.size(); i++)
    {
        FlatVector p = verticesB[i];

        for (int j = 0; j < verticesA.size(); j++)
        {
            FlatVector va = verticesA[j];
            FlatVector vb = verticesA[(j + 1) % verticesA.size()];

            auto result = Collisions::PointSegmentDistance(p, va, vb);
            float distSq = std::get<0>(result);
            FlatVector cp = std::get<1>(result);

            if (FlatMath::NearlyEqual(distSq, minDistSq))
            {
                if (!FlatMath::NearlyEqual(cp, contact1))
                {
                    contact2 = cp;
                    contactCount = 2;
                }
            }
            else if (distSq < minDistSq)
            {
                minDistSq = distSq;
                contactCount = 1;
                contact1 = cp;
            }
        }
    }
    return { contact1, contact2, contactCount};
}


std::tuple<bool, FlatVector, float> Collisions::Collide(FlatBody bodyA, FlatBody bodyB)
{
    FlatVector normal = FlatVector::Zero();
    float depth = 0.0f;

    ShapeType shapeTypeA = bodyA.shapeType;
    ShapeType shapeTypeB = bodyB.shapeType;

    if (shapeTypeA == ShapeType::Box)
    {
        if (shapeTypeB == ShapeType::Box)
        {
            auto result = Collisions::IntersectPolygons(
                bodyA.getPosition(), bodyA.GetTransformedVertices(),
                bodyB.getPosition(), bodyB.GetTransformedVertices());
            return { std::get<0>(result), std::get<1>(result), std::get<2>(result) };
        }
        else if (shapeTypeB == ShapeType::Circle)
        {
            std::cout << "Circles aren't supported yet\n";
        }
    }
    else if (shapeTypeA == ShapeType::Circle)
    {
        std::cout << "Circles aren't supported yet\n";
    }

    return { false, normal, depth };
}

int Collisions::FindClosestPointOnPolygon(FlatVector circleCenter, std::vector<FlatVector> vertices)
{
    int result = -1;
    float minDistance = 3.402823466e+38F;

    for(int i = 0; i < vertices.size(); i++)
    {
        FlatVector v = vertices[i];
        float distance = FlatMath::Distance(v, circleCenter);

        if(distance < minDistance)
        {
            minDistance = distance;
            result = i;
        }
    }

    return result;
}

std::tuple<bool, FlatVector, float> Collisions::IntersectPolygons(FlatVector centerA, std::vector<FlatVector> verticesA, FlatVector centerB,
                                        std::vector<FlatVector> verticesB)
{
    FlatVector normal = FlatVector::Zero();
    float depth = 3.402823466e+38F;
    float minA, minB, maxA, maxB;
    for (int i = 0; i < verticesA.size(); i++)
    {
        FlatVector va = verticesA[i];
        FlatVector vb = verticesA[(i + 1) % verticesA.size()];

        FlatVector edge = vb - va;
        FlatVector axis = FlatVector(-edge.Y, edge.X);
        axis = FlatMath::Normalize(axis);
        auto res1 = Collisions::ProjectVertices(verticesA, axis);
        minA = std::get<0>(res1);
        maxA = std::get<1>(res1);
        auto res = Collisions::ProjectVertices(verticesB, axis);
        minB = std::get<0>(res);
        maxB = std::get<1>(res);

        if (minA >= maxB || minB >= maxA)
        {
            return { false, normal, depth };
        }

        float axisDepth = MIN(maxB - minA, maxA - minB);

        if (axisDepth < depth)
        {
            depth = axisDepth;
            normal = axis;
        }
    }

    for (int i = 0; i < verticesB.size(); i++)
    {
        FlatVector va = verticesB[i];
        FlatVector vb = verticesB[(i + 1) % verticesB.size()];

        FlatVector edge = vb - va;
        FlatVector axis = FlatVector(-edge.Y, edge.X);
        axis = FlatMath::Normalize(axis);

        auto res1 = Collisions::ProjectVertices(verticesA, axis);
        minA = std::get<0>(res1);
        maxA = std::get<1>(res1);
        auto res = Collisions::ProjectVertices(verticesB, axis);
        minB = std::get<0>(res);
        maxB = std::get<1>(res);

        if (minA >= maxB || minB >= maxA)
        {
            return { false, normal, depth };
        }

        float axisDepth = MIN(maxB - minA, maxA - minB);

        if (axisDepth < depth)
        {
            depth = axisDepth;
            normal = axis;
        }
    }

    FlatVector direction = centerB - centerA;

    if (FlatMath::Dot(direction, normal) < 0.0f)
    {
        normal = normal * -1;
    }

    return { true, normal, depth };
}

std::tuple<float, float> Collisions::ProjectVertices(std::vector<FlatVector> vertices, FlatVector axis)
{
    //Возвращает min, max
    float min = 3.402823466e+38F;
    float max = 1.175494351e-38F;

    for(int i = 0; i < vertices.size(); i++)
    {
        FlatVector v = vertices[i];
        float proj = FlatMath::Dot(v, axis);

        if(proj < min) { min = proj; }
        if(proj > max) { max = proj; }
    }
    return { min, max };
}

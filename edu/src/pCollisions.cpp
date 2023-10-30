#include "pCollisions.h"

std::tuple<float, FlatVector> Collisions::PointSegmentDistance(FlatVector p, FlatVector a, FlatVector b,
                                float distanceSquared, FlatVector cp)
{
    // Возвращает distanceSquared, cp
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
        FlatBody bodyA, FlatBody bodyB, FlatVector contact1,
        FlatVector contact2, int contactCount)
{
    // Возвращает contact1, contact2, contactCount
    contact1 = FlatVector::Zero();
    contact2 = FlatVector::Zero();
    contactCount = 0;

    ShapeType shapeTypeA = bodyA.shapeType;
    ShapeType shapeTypeB = bodyB.shapeType;

    if (shapeTypeA == ShapeType::Box)
    {
        if (shapeTypeB == ShapeType::Box)
        {
            auto res = Collisions::FindPolygonsContactPoints(bodyA.GetTransformedVertices(), bodyB.GetTransformedVertices(),
                contact1, contact2, contactCount);
            contact1 = std::get<0>(res);
            contact2 = std::get<1>(res);
            contactCount = std::get<2>(res);
        }
        else if (shapeTypeB == ShapeType::Circle)
        {
            contact1 = Collisions::FindCirclePolygonContactPoint(bodyB.getPosition(), bodyB.Radius,
                                    bodyA.getPosition(), bodyA.GetTransformedVertices(), contact1);
            contactCount = 1;
        }
    }
    else if (shapeTypeA == ShapeType::Circle)
    {
        if (shapeTypeB == ShapeType::Box)
        {
            contact1 = Collisions::FindCirclePolygonContactPoint(bodyA.getPosition(), bodyA.Radius, bodyB.getPosition(), bodyB.GetTransformedVertices(), contact1);
            contactCount = 1;
        }
        else if (shapeTypeB == ShapeType::Circle)
        {
            contact1 = Collisions::FindCirclesContactPoint(bodyA.getPosition(), bodyA.Radius, bodyB.getPosition(), contact1);
            contactCount = 1;
        }
    }
    return { contact1, contact2, contactCount};
}
std::tuple<FlatVector, FlatVector, int> Collisions::FindPolygonsContactPoints(
        std::vector<FlatVector> verticesA, std::vector<FlatVector> verticesB,
        FlatVector contact1, FlatVector contact2, int contactCount)
{
    // Возвращает contact1, contact2 и contactCount
    contact1 = FlatVector::Zero();
    contact2 = FlatVector::Zero();
    contactCount = 0;

    float minDistSq = 3.402823466e+38F;

    for(int i = 0; i < verticesA.size(); i++)
    {
        FlatVector p = verticesA[i];

        for(int j = 0; j < verticesB.size(); j++)
        {
            FlatVector va = verticesB[j];
            FlatVector vb = verticesB[(j + 1) % verticesB.size()];
            float distSq;
            FlatVector cp;
            auto result = Collisions::PointSegmentDistance(p, va, vb, distSq, cp);
            distSq = std::get<0>(result);
            cp = std::get<1>(result);

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

            float distSq;
            FlatVector cp;
            auto result = Collisions::PointSegmentDistance(p, va, vb, distSq, cp);
            distSq = std::get<0>(result);
            cp = std::get<1>(result);

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

FlatVector Collisions::FindCirclePolygonContactPoint(
        FlatVector circleCenter, float circleRadius, FlatVector polygonCenter,
        std::vector<FlatVector> polygonVertices, FlatVector cp)
{
    // Возвращает cp
    cp = FlatVector::Zero();

    float minDistSq = 3.402823466e+38F;

    for(int i = 0; i < polygonVertices.size(); i++)
    {
        FlatVector va = polygonVertices[i];
        FlatVector vb = polygonVertices[(i + 1) % polygonVertices.size()];

        float distSq;
        FlatVector contact;
        auto result = Collisions::PointSegmentDistance(circleCenter, va, vb, distSq, contact);
        distSq = std::get<0>(result);
        contact = std::get<1>(result);

        if(distSq < minDistSq)
        {
            minDistSq = distSq;
            cp = contact;
        }
    }
    return cp;
}

FlatVector Collisions::FindCirclesContactPoint(FlatVector centerA, float radiusA,
FlatVector centerB, FlatVector cp)
{
    FlatVector ab = centerB - centerA;
    FlatVector dir = FlatMath::Normalize(ab);
    cp = centerA + dir * radiusA;
    return cp;
}


std::tuple<bool, FlatVector, float> Collisions::Collide(FlatBody bodyA, FlatBody bodyB,
                                                    FlatVector normal, float depth)
{
    normal = FlatVector::Zero();
    depth = 0.0f;

    ShapeType shapeTypeA = bodyA.shapeType;
    ShapeType shapeTypeB = bodyB.shapeType;

    if (shapeTypeA == ShapeType::Box)
    {
        if (shapeTypeB == ShapeType::Box)
        {
            auto result = Collisions::IntersectPolygons(
                bodyA.getPosition(), bodyA.GetTransformedVertices(),
                bodyB.getPosition(), bodyB.GetTransformedVertices(),
                normal, depth);
            return { std::get<0>(result), std::get<1>(result), std::get<2>(result) };
        }
        else if (shapeTypeB == ShapeType::Circle)
        {
            auto result = Collisions::IntersectCirclePolygon(
                bodyB.getPosition(), bodyB.Radius,
                bodyA.getPosition(), bodyA.GetTransformedVertices(),
                normal, depth);

            normal = normal * -1;
            return { std::get<0>(result), std::get<1>(result), std::get<2>(result) };
        }
    }
    else if (shapeTypeA == ShapeType::Circle)
    {
        if (shapeTypeB == ShapeType::Box)
        {
            auto result = Collisions::IntersectCirclePolygon(
                bodyA.getPosition(), bodyA.Radius,
                bodyB.getPosition(), bodyB.GetTransformedVertices(),
                normal, depth);
            return { std::get<0>(result), std::get<1>(result), std::get<2>(result) };
        }
        else if (shapeTypeB == ShapeType::Circle)
        {
            auto result = Collisions::IntersectCircles(
                bodyA.getPosition(), bodyA.Radius,
                bodyB.getPosition(), bodyB.Radius,
                normal, depth);

            return { std::get<0>(result), std::get<1>(result), std::get<2>(result) };
        }
    }

    return { false, normal, depth };
}

std::tuple<bool, FlatVector, float> Collisions::IntersectCirclePolygon(FlatVector circleCenter, float circleRadius,
                                                FlatVector polygonCenter, std::vector<FlatVector> vertices,
                                                FlatVector normal, float depth)
{
    normal = FlatVector::Zero();
    depth = 3.402823466e+38F;

    FlatVector axis = FlatVector::Zero();
    float axisDepth = 0.0f;
    float minA, maxA, minB, maxB;

    for (int i = 0; i < vertices.size(); i++)
    {
        FlatVector va = vertices[i];
        FlatVector vb = vertices[(i + 1) % vertices.size()];

        FlatVector edge = vb - va;
        axis = FlatVector(-edge.Y, edge.X);
        axis = FlatMath::Normalize(axis);

        auto res1 = Collisions::ProjectVertices(vertices, axis, minA, maxA);
        minA = std::get<0>(res1);
        maxA = std::get<1>(res1);
        auto res = Collisions::ProjectCircle(circleCenter, circleRadius, axis, minB, maxB);
        minB = std::get<0>(res);
        maxB = std::get<1>(res);

        if (minA >= maxB || minB >= maxA)
        {
            return { false, normal, depth };
        }

        axisDepth = MIN(maxB - minA, maxA - minB);

        if (axisDepth < depth)
        {
            depth = axisDepth;
            normal = axis;
        }
    }

    int cpIndex = Collisions::FindClosestPointOnPolygon(circleCenter, vertices);
    FlatVector cp = vertices[cpIndex];

    axis = cp - circleCenter;
    axis = FlatMath::Normalize(axis);

    auto res1 = Collisions::ProjectVertices(vertices, axis, minA, maxA);
    minA = std::get<0>(res1);
    maxA = std::get<1>(res1);
    auto res = Collisions::ProjectCircle(circleCenter, circleRadius, axis, minB, maxB);
    minB = std::get<0>(res);
    maxB = std::get<1>(res);


    if (minA >= maxB || minB >= maxA)
    {
        return { false, normal, depth };
    }

    axisDepth = MIN(maxB - minA, maxA - minB);

    if (axisDepth < depth)
    {
        depth = axisDepth;
        normal = axis;
    }

    FlatVector direction = polygonCenter - circleCenter;

    if (FlatMath::Dot(direction, normal) < 0.0f)
    {
        normal = normal * -1;
    }

    return { true, normal, depth };
}

static int FindClosestPointOnPolygon(FlatVector circleCenter, std::vector<FlatVector> vertices)
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
std::tuple<float, float> Collisions::ProjectCircle(FlatVector center, float radius,
                        FlatVector axis, float min, float max)
{
    // Возвращает min и max
    FlatVector direction = FlatMath::Normalize(axis);
    FlatVector directionAndRadius = direction * radius;

    FlatVector p1 = center + directionAndRadius;
    FlatVector p2 = center - directionAndRadius;

    min = FlatMath::Dot(p1, axis);
    max = FlatMath::Dot(p2, axis);

    if(min > max)
    {
        // swap the min and max values.
        float t = min;
        min = max;
        max = t;
    }
    return { min, max };
}


std::tuple<bool, FlatVector, float> Collisions::IntersectPolygons(FlatVector centerA, std::vector<FlatVector> verticesA, FlatVector centerB,
                                        std::vector<FlatVector> verticesB, FlatVector normal, float depth)
{
    normal = FlatVector::Zero();
    depth = 3.402823466e+38F;
    float minA, minB, maxA, maxB;
    for (int i = 0; i < verticesA.size(); i++)
    {
        FlatVector va = verticesA[i];
        FlatVector vb = verticesA[(i + 1) % verticesA.size()];

        FlatVector edge = vb - va;
        FlatVector axis = FlatVector(-edge.Y, edge.X);
        axis = FlatMath::Normalize(axis);
        auto res1 = Collisions::ProjectVertices(verticesA, axis, minA, maxA);
        minA = std::get<0>(res1);
        maxA = std::get<1>(res1);
        auto res = Collisions::ProjectVertices(verticesB, axis, minA, maxA);
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

        auto res1 = Collisions::ProjectVertices(verticesA, axis, minA, maxA);
        minA = std::get<0>(res1);
        maxA = std::get<1>(res1);
        auto res = Collisions::ProjectVertices(verticesB, axis, minA, maxA);
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

std::tuple<float, float> ProjectVertices(std::vector<FlatVector> vertices, FlatVector axis,
                                        float min, float max)
{
    //Возвращает min, max
    min = 3.402823466e+38F;
    max = 1.175494351e-38F;

    for(int i = 0; i < vertices.size(); i++)
    {
        FlatVector v = vertices[i];
        float proj = FlatMath::Dot(v, axis);

        if(proj < min) { min = proj; }
        if(proj > max) { max = proj; }
    }
    return { min, max };
}

std::tuple<bool, FlatVector, float> Collisions::IntersectCircles(
        FlatVector centerA, float radiusA,
        FlatVector centerB, float radiusB,
        FlatVector normal, float depth)
{
    normal = FlatVector::Zero();
    depth = 0.0f;

    float distance = FlatMath::Distance(centerA, centerB);
    float radii = radiusA + radiusB;

    if(distance >= radii)
    {
        return { false, normal, depth };
    }

    normal = FlatMath::Normalize(centerB - centerA);
    depth = radii - distance;

    return { true, normal, depth };
}

#ifndef _P_BODY_H
#define _P_BODY_H

#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "pVector.h"

enum ShapeType
{
    Circle = 0,
    Box = 1,
};

struct FlatAABB
{
    FlatVector Min;
    FlatVector Max;

    FlatAABB() { this->Min = this->Max = FlatVector(0.0f); }

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

class FlatBody
{
private:
    FlatVector position;
    FlatVector linearVelocity;
    float angle;
    float angularVelocity;
    FlatVector force;
    std::vector<FlatVector> vertices;
    std::vector<FlatVector> transformedVertices;
    FlatAABB aabb;

    bool transformUpdateRequired;
    bool aabbUpdateRequired;
public:
    ShapeType shapeType;
    float Density;
    float Mass;
    float InvMass;
    float Restitution;
    float Area;
    float Inertia;
    float InvInertia;
    bool IsStatic;
    float Radius;
    float Width;
    float Height;
    float StaticFriction;
    float DynamicFriction;

    FlatBody(float density, float mass, float inertia, float restitution, float area,
            bool isStatic, float radius, float width, float height,
            std::vector<FlatVector> vertices, ShapeType shapeType);

    FlatVector getPosition() { return position; }

    FlatVector getLinearVelocity() { return linearVelocity; }
    void setLinearVelocity(FlatVector linVel) { linearVelocity = linVel; }

    float getAngularVelocity() { return angularVelocity; }
    void setAngularVelocity(float angVel) { angularVelocity = angVel; }
    std::vector<FlatVector> GetTransformedVertices();
    FlatAABB GetAABB();
    void Step(float time, FlatVector gravity, int iterations);
    void Move(FlatVector amount);
    void MoveTo(FlatVector position);
    void Rotate(float amount);
    void RotateTo(float angle);
    void AddForce(FlatVector amount);

    static FlatBody* FlatBody::CreateCircleBody(float radius, float density,
                                    bool isStatic, float restitution);
    static FlatBody* CreateBoxBody(float width, float height, float density,
                                    bool isStatic, float restitution);

    static std::vector<FlatVector> CreateBoxVertices(float width, float height)
};

#endif // _P_BODY_H

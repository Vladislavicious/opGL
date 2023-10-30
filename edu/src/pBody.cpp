#include "pBody.h"


FlatBody::FlatBody(float density, float mass, float inertia, float restitution, float area,
        bool isStatic, float radius, float width, float height, std::vector<FlatVector> vertices, ShapeType shapeType)
{
    this->position = FlatVector::Zero();
    this->linearVelocity = FlatVector::Zero();
    this->angle = 0.0f;
    this->angularVelocity = 0.0f;
    this->force = FlatVector::Zero();

    this->shapeType = shapeType;
    this->Density = density;
    this->Mass = mass;
    this->InvMass = mass > 0.0f ? 1.0f / mass : 0.0f;
    this->Inertia = inertia;
    this->InvInertia = inertia > 0.0f ? 1.0f / inertia : 0.0f;
    this->Restitution = restitution;
    this->Area = area;
    this->IsStatic = isStatic;
    this->Radius = radius;
    this->Width = width;
    this->Height = height;
    this->StaticFriction = 0.6f;
    this->DynamicFriction = 0.4f;

    if(this->shapeType == ShapeType::Box)
    {
        this->vertices = vertices;
        //this->transformedVertices = new FlatVector[this->vertices.size()];
    }
    else
    {
       // this->vertices = nullptr;
       // this->transformedVertices = nullptr;
    }

    this->transformUpdateRequired = true;
    this->aabbUpdateRequired = true;
}

std::vector<FlatVector> FlatBody::CreateBoxVertices(float width, float height)
{
    float left = -width / 2.0f;
    float right = left + width;
    float bottom = -height / 2.0f;
    float top = bottom + height;

    std::vector<FlatVector> vertices;
    vertices.push_back(FlatVector(left, top));
    vertices.push_back(FlatVector(right, top));
    vertices.push_back(FlatVector(right, bottom));
    vertices.push_back(FlatVector(left, bottom));

    return vertices;
}

std::vector<FlatVector> FlatBody::GetTransformedVertices()
{
    if(this->transformUpdateRequired)
    {
        FlatTransform transform = FlatTransform(this->position, this->angle);

        for(int i = 0; i < this->vertices.size(); i++)
        {
            FlatVector v = this->vertices[i];
            this->transformedVertices[i] = FlatVector::Transform(v, transform);
        }

        FlatWorld::TransformCount++;
    }
    else
    {
        FlatWorld::NoTransformCount++;
    }

    this->transformUpdateRequired = false;
    return this->transformedVertices;
}

FlatAABB FlatBody::GetAABB()
{
    if (this->aabbUpdateRequired)
    {
        float minX = 3.402823466e+38F;
        float minY = 3.402823466e+38F;
        float maxX = 1.175494351e-38F;
        float maxY = 1.175494351e-38F;

        if (this->shapeType == ShapeType::Box)
        {
            std::vector<FlatVector> vertices = this->GetTransformedVertices();

            for (int i = 0; i < vertices.size(); i++)
            {
                FlatVector v = vertices[i];

                if (v.X < minX) { minX = v.X; }
                if (v.X > maxX) { maxX = v.X; }
                if (v.Y < minY) { minY = v.Y; }
                if (v.Y > maxY) { maxY = v.Y; }
            }
        }
        else if (this->shapeType == ShapeType::Circle)
        {
            minX = this->position.X - this->Radius;
            minY = this->position.Y - this->Radius;
            maxX = this->position.X + this->Radius;
            maxY = this->position.Y + this->Radius;
        }
        else
        {
            std::cout << "Unknown ShapeType" << std::endl;
        }

        this->aabb = FlatAABB(minX, minY, maxX, maxY);
    }

    this->aabbUpdateRequired = false;
    return this->aabb;
}

void FlatBody::Step(float time, FlatVector gravity, int iterations)
{
    if(this->IsStatic)
    {
        return;
    }

    time /= (float)iterations;

    this->linearVelocity = this->linearVelocity + gravity * time;
    this->position = this->linearVelocity + this->linearVelocity * time;

    this->angle += this->angularVelocity * time;

    this->force = FlatVector::Zero();
    this->transformUpdateRequired = true;
    this->aabbUpdateRequired = true;
}

void FlatBody::Move(FlatVector amount)
{
    this->position = this->position + amount;
    this->transformUpdateRequired = true;
    this->aabbUpdateRequired = true;
}

void FlatBody::MoveTo(FlatVector position)
{
    this->position = position;
    this->transformUpdateRequired = true;
    this->aabbUpdateRequired = true;
}

void FlatBody::Rotate(float amount)
{
    this->angle += amount;
    this->transformUpdateRequired = true;
    this->aabbUpdateRequired = true;
}

void FlatBody::RotateTo(float angle)
{
    this->angle = angle;
    this->transformUpdateRequired = true;
    this->aabbUpdateRequired = true;
}

void FlatBody::AddForce(FlatVector amount)
{
    this->force = amount;
}

FlatBody* FlatBody::CreateCircleBody(float radius, float density, bool isStatic, float restitution)
{
    FlatBody* body = nullptr;
    std::string errorMessage = "";

    float area = radius * radius * glm::pi<float>();

    if(area < FlatWorld::MinBodySize)
    {
        errorMessage = "Circle radius is too small. Min circle area is " + std::string(FlatWorld::MinBodySize);
    }

    if(area > FlatWorld::MaxBodySize)
    {
        errorMessage = "Circle radius is too large. Max circle area is " + std::string(FlatWorld::MaxBodySize);
    }

    if (density < FlatWorld::MinDensity)
    {
        errorMessage = "Density is too small. Min density is " + std::string(FlatWorld::MinDensity);
    }

    if (density > FlatWorld::MaxDensity)
    {
        errorMessage = "Density is too large. Max density is " + FlatWorld::MaxDensity;
    }

    if (errorMessage != "")
    {
        std::cout << errorMessage << std::endl;
        return nullptr;
    }


    restitution = FlatMath::Clamp(restitution, 0.0f, 1.0f);

    float mass = 0.0f;
    float inertia = 0.0f;

    if (!isStatic)
    {
        // mass = area * depth * density
        mass = area * density;
        inertia = (1.0f / 2.0f) * mass * radius * radius;
    }
    std::vector<FlatVector> temp;

    body = new FlatBody(density, mass, inertia, restitution, area, isStatic,
                        radius, 0.0f, 0.0f, temp, ShapeType::Circle);
    return body;
}

FlatBody* FlatBody::CreateBoxBody(float width, float height, float density,
                                    bool isStatic, float restitution)
{
    FlatBody* body = nullptr;
    std::string errorMessage = "";

    float area = width * height;

        if(area < FlatWorld::MinBodySize)
    {
        errorMessage = "Area is too small. Min area is " + std::string(FlatWorld::MinBodySize);
    }

    if(area > FlatWorld::MaxBodySize)
    {
        errorMessage = "Area is too large. Max area is " + std::string(FlatWorld::MaxBodySize);
    }

    if (density < FlatWorld::MinDensity)
    {
        errorMessage = "Density is too small. Min density is " + std::string(FlatWorld::MinDensity);
    }

    if (density > FlatWorld::MaxDensity)
    {
        errorMessage = "Density is too large. Max density is " + FlatWorld::MaxDensity;
    }

    if (errorMessage != "")
    {
        std::cout << errorMessage << std::endl;
        return nullptr;
    }

    restitution = FlatMath::Clamp(restitution, 0.0f, 1.0f);

    float mass = 0.0f;
    float inertia = 0.0f;

    if (!isStatic)
    {
        // mass = area * depth * density
        mass = area * density;
        inertia = (1.0f / 12) * mass * (width * width + height * height);
    }

    std::vector<FlatVector> vertices = FlatBody::CreateBoxVertices(width, height);

    body = new FlatBody(density, mass, inertia, restitution, area, isStatic,
                        0.0f, width, height, vertices, ShapeType::Box);
    return body;
}

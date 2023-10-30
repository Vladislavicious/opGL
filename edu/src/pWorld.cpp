#include "pWorld.h"



int FlatWorld::TransformCount = 0;
int FlatWorld::NoTransformCount = 0;
float FlatWorld::MinBodySize = 0.01f * 0.01f;
float FlatWorld::MaxBodySize = 64.0f * 64.0f;

float FlatWorld::MinDensity = 0.5f;     // g/cm^3
float FlatWorld::MaxDensity = 21.4f;

int FlatWorld::MinIterations = 1;
int FlatWorld::MaxIterations = 128;

void FlatWorld::BroadPhase()
{
for (int i = 0; i < this->bodyList.size() - 1; i++)
{
    FlatBody bodyA = this->bodyList[i];
    FlatAABB bodyA_aabb = bodyA.GetAABB();

    for (int j = i + 1; j < this->bodyList.size(); j++)
    {
        FlatBody bodyB = this->bodyList[j];
        FlatAABB bodyB_aabb = bodyB.GetAABB();

        if (bodyA.IsStatic && bodyB.IsStatic)
        {
            continue;
        }

        if (!Collisions.IntersectAABBs(bodyA_aabb, bodyB_aabb))
        {
            continue;
        }

        this->contactPairs.push_back(Pair(i, j));
    }
}
}

void FlatWorld::NarrowPhase()
{
    for (int i = 0; i < this->contactPairs.size(); i++)
    {
        Pair pair = this->contactPairs[i];
        FlatBody bodyA = this->bodyList[pair.Item1];
        FlatBody bodyB = this->bodyList[pair.Item2];

        FlatVector normal;
        float depth;
        auto res = Collisions::Collide(bodyA, bodyB, normal, depth);
        if ( std::get<0>(res) )
        {
            normal = std::get<1>(res);
            depth = std::get<2>(res);
            this->SeparateBodies(bodyA, bodyB, normal * depth);
            Collisions.FindContactPoints(bodyA, bodyB, out FlatVector contact1, out FlatVector contact2, out int contactCount);
            FlatManifold contact(bodyA, bodyB, normal, depth, contact1, contact2, contactCount);
            this->ResolveCollisionWithRotationAndFriction(contact);
        }

    }
}

void FlatWorld::SeparateBodies(FlatBody bodyA, FlatBody bodyB, FlatVector mtv)
{
    if (bodyA.IsStatic)
    {
        bodyB.Move(mtv);
    }
    else if (bodyB.IsStatic)
    {
        bodyA.Move(mtv * - 1);
    }
    else
    {
        bodyA.Move(mtv * - 1 / 2.0f);
        bodyB.Move(mtv / 2.0f);
    }
}

FlatWorld::FlatWorld()
{
    this->gravity = FlatVector(0.0f, -9.81f);
    this->contactList.reserve(2);
    this->impulseList.reserve(2);
    this->raList.reserve(2);
    this->rbList.reserve(2);
    this->frictionImpulseList.reserve(2);
    this->jList.reserve(2);
}

void FlatWorld::Step(float time, int totalIterations)
{
    totalIterations = FlatMath::Clamp(totalIterations, FlatWorld::MinIterations, FlatWorld::MaxIterations);

    for (int currentIteration = 0; currentIteration < totalIterations; currentIteration++)
    {
        this->contactPairs.clear();
        this->StepBodies(time, totalIterations);
        this->BroadPhase();
        this->NarrowPhase();
    }
}

void FlatWorld::StepBodies(float time, int totalIterations)
{
    for (int i = 0; i < this->bodyList.size(); i++)
    {
        this->bodyList[i].Step(time, this->gravity, totalIterations);
    }
}

void FlatWorld::ResolveCollisionBasic(FlatManifold& contact)
{
    FlatBody bodyA = contact.BodyA;
    FlatBody bodyB = contact.BodyB;
    FlatVector normal = contact.Normal;
    float depth = contact.Depth;

    FlatVector relativeVelocity = bodyB.getLinearVelocity() - bodyA.getLinearVelocity();

    if (FlatMath::Dot(relativeVelocity, normal) > 0.0f)
    {
        return;
    }

    float e = MIN(bodyA.Restitution, bodyB.Restitution);

    float j = -(1.0f + e) * FlatMath::Dot(relativeVelocity, normal);
    j /= bodyA.InvMass + bodyB.InvMass;

    FlatVector impulse = normal * j;
    bodyA.setLinearVelocity( bodyA.getLinearVelocity() * bodyA.InvMass );
    bodyB.setLinearVelocity( bodyB.getLinearVelocity() * bodyB.InvMass );
}


void FlatWorld::ResolveCollisionWithRotation(FlatManifold& contact)
{
    FlatBody bodyA = contact.BodyA;
    FlatBody bodyB = contact.BodyB;
    FlatVector normal = contact.Normal;
    FlatVector contact1 = contact.Contact1;
    FlatVector contact2 = contact.Contact2;
    int contactCount = contact.ContactCount;

    float e = MIN(bodyA.Restitution, bodyB.Restitution);

    this->contactList[0] = contact1;
    this->contactList[1] = contact2;

    for(int i = 0; i < contactCount; i++)
    {
        this->impulseList[i] = FlatVector::Zero();
        this->raList[i] = FlatVector::Zero();
        this->rbList[i] = FlatVector::Zero();
    }

    for(int i = 0; i < contactCount; i++)
    {
        FlatVector ra = contactList[i] - bodyA.getPosition();
        FlatVector rb = contactList[i] - bodyB.getPosition();

        raList[i] = ra;
        rbList[i] = rb;

        FlatVector raPerp = FlatVector(-ra.Y, ra.X);
        FlatVector rbPerp = FlatVector(-rb.Y, rb.X);

        FlatVector angularLinearVelocityA = raPerp * bodyA.getAngularVelocity();
        FlatVector angularLinearVelocityB = rbPerp * bodyB.getAngularVelocity();

        FlatVector relativeVelocity =
            (bodyB.getLinearVelocity() + angularLinearVelocityB) -
            (bodyA.getLinearVelocity() + angularLinearVelocityA);

        float contactVelocityMag = FlatMath::Dot(relativeVelocity, normal);

        if (contactVelocityMag > 0.0f)
        {
            continue;
        }

        float raPerpDotN = FlatMath::Dot(raPerp, normal);
        float rbPerpDotN = FlatMath::Dot(rbPerp, normal);

        float denom = bodyA.InvMass + bodyB.InvMass +
            (raPerpDotN * raPerpDotN) * bodyA.InvInertia +
            (rbPerpDotN * rbPerpDotN) * bodyB.InvInertia;

        float j = -(1.0f + e) * contactVelocityMag;
        j /= denom;
        j /= (float)contactCount;

        FlatVector impulse = normal * j;
        impulseList[i] = impulse;
    }

    for(int i = 0; i < contactCount; i++)
    {
        FlatVector impulse = impulseList[i];
        FlatVector ra = raList[i];
        FlatVector rb = rbList[i];
        bodyA.setLinearVelocity( bodyA.getLinearVelocity() -impulse * bodyA.InvMass );
        bodyA.setAngularVelocity( bodyA.getAngularVelocity() -FlatMath::Cross(ra, impulse) * bodyA.InvInertia );
        bodyB.setLinearVelocity( bodyB.getLinearVelocity() + impulse * bodyB.InvMass );
        bodyB.setAngularVelocity( bodyB.getAngularVelocity() + FlatMath::Cross(rb, impulse) * bodyB.InvInertia );
    }
}

void FlatWorld::ResolveCollisionWithRotationAndFriction(FlatManifold& contact)
{
    FlatBody bodyA = contact.BodyA;
    FlatBody bodyB = contact.BodyB;
    FlatVector normal = contact.Normal;
    FlatVector contact1 = contact.Contact1;
    FlatVector contact2 = contact.Contact2;
    int contactCount = contact.ContactCount;

    float e = MIN(bodyA.Restitution, bodyB.Restitution);

    float sf = (bodyA.StaticFriction + bodyB.StaticFriction) * 0.5f;
    float df = (bodyA.DynamicFriction + bodyB.DynamicFriction) * 0.5f;

    this->contactList[0] = contact1;
    this->contactList[1] = contact2;

    for (int i = 0; i < contactCount; i++)
    {
        this->impulseList[i] = FlatVector::Zero();
        this->raList[i] = FlatVector::Zero();
        this->rbList[i] = FlatVector::Zero();
        this->frictionImpulseList[i] = FlatVector::Zero();
        this->jList[i] = 0.0f;
    }

    for (int i = 0; i < contactCount; i++)
    {
        FlatVector ra = contactList[i] - bodyA.getPosition();
        FlatVector rb = contactList[i] - bodyB.getPosition();

        raList[i] = ra;
        rbList[i] = rb;

        FlatVector raPerp = FlatVector(-ra.Y, ra.X);
        FlatVector rbPerp = FlatVector(-rb.Y, rb.X);

        FlatVector angularLinearVelocityA = raPerp * bodyA.getAngularVelocity();
        FlatVector angularLinearVelocityB = rbPerp * bodyB.getAngularVelocity();

        FlatVector relativeVelocity =
            (bodyB.getLinearVelocity() + angularLinearVelocityB) -
            (bodyA.getLinearVelocity() + angularLinearVelocityA);

        float contactVelocityMag = FlatMath::Dot(relativeVelocity, normal);

        if (contactVelocityMag > 0.0f)
        {
            continue;
        }

        float raPerpDotN = FlatMath::Dot(raPerp, normal);
        float rbPerpDotN = FlatMath::Dot(rbPerp, normal);

        float denom = bodyA.InvMass + bodyB.InvMass +
            (raPerpDotN * raPerpDotN) * bodyA.InvInertia +
            (rbPerpDotN * rbPerpDotN) * bodyB.InvInertia;

        float j = -(1.0f + e) * contactVelocityMag;
        j /= denom;
        j /= (float)contactCount;

        jList[i] = j;

        FlatVector impulse = normal * j;
        impulseList[i] = impulse;
    }

    for (int i = 0; i < contactCount; i++)
    {
        FlatVector impulse = impulseList[i];
        FlatVector ra = raList[i];
        FlatVector rb = rbList[i];

        bodyA.setLinearVelocity( bodyA.getLinearVelocity() -impulse * bodyA.InvMass );
        bodyA.setAngularVelocity( bodyA.getAngularVelocity() -FlatMath::Cross(ra, impulse) * bodyA.InvInertia );
        bodyB.setLinearVelocity( bodyB.getLinearVelocity() + impulse * bodyB.InvMass );
        bodyB.setAngularVelocity( bodyB.getAngularVelocity() + FlatMath::Cross(rb, impulse) * bodyB.InvInertia );
    }

    for (int i = 0; i < contactCount; i++)
    {
        FlatVector ra = contactList[i] - bodyA.getPosition();
        FlatVector rb = contactList[i] - bodyB.getPosition();

        raList[i] = ra;
        rbList[i] = rb;

        FlatVector raPerp = FlatVector(-ra.Y, ra.X);
        FlatVector rbPerp = FlatVector(-rb.Y, rb.X);

        FlatVector angularLinearVelocityA = raPerp * bodyA.getAngularVelocity();
        FlatVector angularLinearVelocityB = rbPerp * bodyB.getAngularVelocity();

        FlatVector relativeVelocity =
            (bodyB.getLinearVelocity() + angularLinearVelocityB) -
            (bodyA.getLinearVelocity() + angularLinearVelocityA);

        FlatVector tangent = relativeVelocity - normal * FlatMath::Dot(relativeVelocity, normal);

        if(FlatMath::NearlyEqual(tangent, FlatVector::Zero()))
        {
            continue;
        }
        else
        {
            tangent = FlatMath::Normalize(tangent);
        }

        float raPerpDotT = FlatMath::Dot(raPerp, tangent);
        float rbPerpDotT = FlatMath::Dot(rbPerp, tangent);

        float denom = bodyA.InvMass + bodyB.InvMass +
            (raPerpDotT * raPerpDotT) * bodyA.InvInertia +
            (rbPerpDotT * rbPerpDotT) * bodyB.InvInertia;

        float jt = -FlatMath::Dot(relativeVelocity, tangent);
        jt /= denom;
        jt /= (float)contactCount;

        FlatVector frictionImpulse;
        float j = jList[i];

        if(abs(jt) <= j * sf)
        {
            frictionImpulse = tangent * jt;
        }
        else
        {
            frictionImpulse = tangent * -j * df;
        }

        this->frictionImpulseList[i] = frictionImpulse;
    }

    for (int i = 0; i < contactCount; i++)
    {
        FlatVector frictionImpulse = this->frictionImpulseList[i];
        FlatVector ra = raList[i];
        FlatVector rb = rbList[i];

        bodyA.setLinearVelocity( bodyA.getLinearVelocity() -frictionImpulse * bodyA.InvMass );
        bodyA.setAngularVelocity( bodyA.getAngularVelocity() -FlatMath::Cross(ra, frictionImpulse) * bodyA.InvInertia );
        bodyB.setLinearVelocity( bodyB.getLinearVelocity() + frictionImpulse * bodyB.InvMass );
        bodyB.setAngularVelocity( bodyB.getAngularVelocity() + FlatMath::Cross(rb, frictionImpulse) * bodyB.InvInertia );
    }
}

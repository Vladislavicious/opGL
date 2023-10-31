#ifndef _P_WORLD_H
#define _P_WORLD_H
#include "pVector.h"
#include "pBody.h"
#include "pCollisions.h"
#include <vector>
#include <tuple>
class FlatBody;
#include "pManifold.h"
struct FlatManifold;

#define MIN(a, b) a > b?b:a

struct Pair
{
    int Item1, Item2;
    Pair(): Item1(0), Item2(0) {}
    Pair(int a, int b): Item1(a), Item2(b) {}
};

class FlatWorld
{
private:
    FlatVector gravity;
    std::vector<FlatBody> bodyList;
    std::vector<Pair> contactPairs;

    std::vector<FlatVector> contactList;
    std::vector<FlatVector> impulseList;
    std::vector<FlatVector> raList;
    std::vector<FlatVector> rbList;
    std::vector<FlatVector> frictionImpulseList;
    std::vector<float> jList;

    void BroadPhase();

    void NarrowPhase();

    void SeparateBodies(FlatBody bodyA, FlatBody bodyB, FlatVector mtv);
public:

    static int TransformCount;
    static int NoTransformCount;

    static float MinBodySize;
    static float MaxBodySize;

    static float MinDensity;     // g/cm^3
    static float MaxDensity;

    static int MinIterations;
    static int MaxIterations;


    FlatWorld();

    int getBodyCount() { return this->bodyList.size(); }

    void AddBody(FlatBody& body)
    {
        this->bodyList.push_back(body);
    }

    bool RemoveBody(FlatBody& body)
    {
        //bodyList.erase(std::remove(bodyList.begin(), bodyList.end(), body), bodyList.end());
        std::cout << "not implemented RemoveBody\n";
        return false;
    }

    FlatBody* GetBody(int index)
    {
        FlatBody* body = nullptr;

        if(index < 0 || index >= this->bodyList.size())
        {
            body = &this->bodyList[index];
        }

        return body;
    }

    void Step(float time, int totalIterations);

    void StepBodies(float time, int totalIterations);

    void ResolveCollisionWithRotationAndFriction(FlatManifold& contact);
};

#endif // _P_WORLD_H

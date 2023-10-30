#ifndef _P_VECTOR_H
#define _P_VECTOR_H
#include <iostream>
#include <math.h>
struct FlatVector;
struct FlatTransform;

class FlatMath
{
public:
    static const float VerySmallAmount = 0.0005f;

    static float Clamp(float value, float min, float max)
    {
        if(min == max)
        {
            return min;
        }

        if(min > max)
        {
            std::cout<< "min is greater than the max." << std::endl;
        }

        if(value < min)
        {
            return min;
        }

        if(value > max)
        {
            return max;
        }

        return value;
    }

    static int Clamp(int value, int min, int max)
    {
        if (min == max)
        {
            return min;
        }

        if (min > max)
        {
            std::cout<< "min is greater than the max." << std::endl;
        }

        if (value < min)
        {
            return min;
        }

        if (value > max)
        {
            return max;
        }

        return value;
    }

    static float LengthSquared(FlatVector v)
    {
        return v.X * v.X + v.Y * v.Y;
    }

    static float Length(FlatVector v)
    {
        return sqrt(v.X * v.X + v.Y * v.Y);
    }

    static float DistanceSquared(FlatVector a, FlatVector b)
    {
        float dx = a.X - b.X;
        float dy = a.Y - b.Y;
        return dx * dx + dy * dy;
    }

    static float Distance(FlatVector a, FlatVector b)
    {
        float dx = a.X - b.X;
        float dy = a.Y - b.Y;
        return sqrt(dx * dx + dy * dy);
    }

    static FlatVector Normalize(FlatVector v)
    {
        float len = FlatMath::Length(v);
        return FlatVector(v.X / len, v.Y / len);
    }

    static float Dot(FlatVector a, FlatVector b)
    {
        // a · b = ax * bx + ay * by
        return a.X * b.X + a.Y * b.Y;
    }

    static float Cross(FlatVector a, FlatVector b)
    {
        // cz = ax * by − ay * bx
        return a.X * b.Y - a.Y * b.X;
    }

    static bool NearlyEqual(float a, float b)
    {
        return abs(a - b) < FlatMath::VerySmallAmount;
    }

    static bool NearlyEqual(FlatVector a, FlatVector b)
    {
        return FlatMath::DistanceSquared(a, b) < FlatMath::VerySmallAmount * FlatMath::VerySmallAmount;
    }
};

struct FlatTransform
{
    static FlatTransform Zero() { return FlatTransform(0.0f, 0.0f, 0.0f); }

    float PositionX;
    float PositionY;
    float Sin;
    float Cos;

    FlatTransform(FlatVector position, float angle)
    {
        this->PositionX = position.X;
        this->PositionY = position.Y;
        this->Sin = sin(angle);
        this->Cos = cos(angle);
    }

    FlatTransform(float x, float y, float angle)
    {
        this->PositionX = x;
        this->PositionY = y;
        this->Sin = sin(angle);
        this->Cos = cos(angle);
    }
};

struct FlatVector
{
    float X;
    float Y;

    static FlatVector Zero() { return FlatVector(0.0f, 0.0f); }

    FlatVector(): X(0.0f), Y(0.0f) {}
    FlatVector(float x, float y)
    {
        this->X = x;
        this->Y = y;
    }

    FlatVector operator+(FlatVector b)
    {
        return FlatVector(this->X + b.X, this->Y + b.Y);
    }

    FlatVector operator-(FlatVector b)
    {
        return FlatVector(this->X - b.X, this->Y - b.Y);
    }

   FlatVector operator-(FlatVector v)
    {
        return FlatVector(-this->X, -this->Y);
    }

    FlatVector operator*(float s)
    {
        return FlatVector(this->X * s, this->Y * s);
    }


    FlatVector operator/(float s)
    {
        return FlatVector(this->X / s, this->Y / s);
    }

    static FlatVector Transform(FlatVector v, FlatTransform transform)
    {
        return FlatVector(
            transform.Cos * v.X - transform.Sin * v.Y + transform.PositionX,
            transform.Sin * v.X + transform.Cos * v.Y + transform.PositionY);
    }

    bool Equals(FlatVector other)
    {
        return this->X == other.X && this->Y == other.Y;
    }
};

#endif // _P_VECTOR_H

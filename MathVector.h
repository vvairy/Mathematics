#pragma once
#include "Dot.h"
class MathVector
{
public:
    double x, y, z;
    MathVector(double x, double y, double z) : x(x), y(y), z(z) {}

    MathVector(Dot a, Dot b) : x(a.x - b.x), y(a.y - b.y), z(a.z - b.z) {}

    MathVector(Dot dot) : x(dot.x), y(dot.y), z(dot.z) {}

    MathVector() { }

    bool operator== (MathVector B); //Vectors are equal if they have same coordinates
    MathVector operator^ (MathVector B);//Vector Multiplication Of Vectors
    MathVector operator* (double n);
    double operator* (MathVector B);

    static double moduleOfVector(MathVector A);
    static double angleBetweenVectors(MathVector A, MathVector B);
    void normalize();

    double volumeOfParallelepipedOnVectors(MathVector A, MathVector B, MathVector C);
    double volumeOfPiramidOnVectors(MathVector A, MathVector B, MathVector C);
};
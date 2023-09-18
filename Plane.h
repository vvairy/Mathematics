#pragma once
#include "Line.h"
class Plane : MathVector
{
public:
    Plane(MathVector normalVector, Dot dotOnLine);

    static double angleBetweenPlanes(Plane A, Plane B);
    double angleBetweenLineAndPlane(Line line);
    static std::optional<Line> findIntersectionOfPlanes(Plane A, Plane B);
    static Dot get—ommonDotOfPlanes(Plane A, Plane B);
    double distanceToDot(Dot dot);
    double distanceToLine(Line line);
    const char* relativePositionWithLine(Line line);
    std::optional<Dot> getDotOfIntersectionWithLine(Line line);
private:
    MathVector normalVector;
    Dot planeDot;
};
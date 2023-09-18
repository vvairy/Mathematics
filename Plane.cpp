#include "Plane.h"
Plane::Plane(MathVector normalVector, Dot dotOnLine) : MathVector(normalVector)
{
    this->planeDot = Dot(dotOnLine);
    this->normalVector = MathVector(normalVector);
}

double Plane::angleBetweenPlanes(Plane A, Plane B)
{
    return acos(A.normalVector * B.normalVector / moduleOfVector(A.normalVector) / moduleOfVector(B.normalVector));
}

double Plane::angleBetweenLineAndPlane(Line line)
{
    return asin(this->normalVector * line.guideVector / moduleOfVector(this->normalVector) / moduleOfVector(line.guideVector));
}

std::optional<Line> Plane::findIntersectionOfPlanes(Plane A, Plane B)
{
    if (A.normalVector == B.normalVector)
    {
        std::cout << "No Line: Planes are parallel\n"; return std::nullopt;
    }
    return Line(A.normalVector ^ B.normalVector, getÑommonDotOfPlanes(A, B));
}

Dot Plane::getÑommonDotOfPlanes(Plane A, Plane B)
{
    double D1 = A.normalVector * MathVector(A.planeDot); // Plane equation: Ax + By + Cz + D = 0
    double D2 = A.normalVector * MathVector(B.planeDot); // D1 and D2 - D in themselves equations
    double x = (D1 * B.planeDot.y - D2 * A.planeDot.x) /
        (A.planeDot.x * B.planeDot.y - B.planeDot.x * A.planeDot.y);
    double y = (D2 * B.planeDot.x - D1 * A.planeDot.y) /
        (A.planeDot.x * B.planeDot.y - B.planeDot.x * A.planeDot.y);
    return Dot(x, y, 0);
}

double Plane::distanceToDot(Dot dot)
{
    double D = this->normalVector * MathVector(this->planeDot);
    return D + this->normalVector * MathVector(dot) / moduleOfVector(this->normalVector);
}

double Plane::distanceToLine(Line line)
{
    if (line.guideVector * this->normalVector != 0) //if normal vector is not perpendicular to guide vector -> 
        return 0; //line is not parallel to plane -> line crosses plane somewhere
    else
        return distanceToDot(line.dot);
}

const char* Plane::relativePositionWithLine(Line line)
{
    if (this->normalVector * line.guideVector != 0)
        return "Line intersects plane";
    if (distanceToDot(line.dot) != 0)
        return "Line is parallel to plane";
    else
        return "Line lies in plane";
}

std::optional<Dot> Plane::getDotOfIntersectionWithLine(Line line)
{
    if (relativePositionWithLine(line) == "Line is parallel to plane")
    {
        std::cout << "No intersection Dots\n"; return std::nullopt;
    }
    double parametr = -(this->normalVector * MathVector(line.dot));
    parametr /= this->normalVector * line.guideVector;
    double x = parametr * line.guideVector.x - line.dot.x;
    double y = parametr * line.guideVector.y - line.dot.y;
    double z = parametr * line.guideVector.z - line.dot.z;
    return Dot(x, y, z);
}

MathVector normalVector;
Dot planeDot;
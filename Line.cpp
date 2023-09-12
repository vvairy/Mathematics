#include "Line.h"

Line::Line(MathVector guideVector, Dot dotOnLine) : MathVector(guideVector)
{
    this->dot = Dot(dotOnLine);
    this->guideVector = MathVector(guideVector);
}

double Line::distanceBetweenLines(Line A, Line B)
{
    if (moduleOfVector(A.guideVector ^ B.guideVector) == 0)
        return 0;
    MathVector distanceBetweenRandomDots = { A.dot, B.dot };
    return abs((A.guideVector ^ B.guideVector) * distanceBetweenRandomDots / moduleOfVector(A.guideVector ^ B.guideVector));
}

double Line::distanceToDot(Dot dot)
{
    return (this->guideVector * MathVector(dot) / moduleOfVector(this->guideVector));
}
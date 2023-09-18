#pragma once
#include "MathVector.h"

class Line : public MathVector
{
public:
    Line(MathVector guideVector, Dot dotOnLine);

    static double distanceBetweenLines(Line A, Line B);
    static double angleBetweenLines(Line A, Line B);

    double distanceToDot(Dot dot);
    bool isDotOnLine(Dot dot);

    Dot dot;
    MathVector guideVector;
};
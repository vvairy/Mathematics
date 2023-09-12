#pragma once
#include "Matrix.h"
#include <array>
#include <vector>
using std::vector;
struct Dot
{
    double x, y, z;
    Dot(double x, double y, double z) : x(x), y(y), z(z) {}

    Dot(std::array<double, 3> coordinates) : x(coordinates[0]), y(coordinates[1]), z(coordinates[2]) {}

    Dot() : x(0), y(0), z(0) {}

    static double distanceBetweenDots(Dot A, Dot B);
    static bool areInOnePLane(vector <Dot> Dots);
    std::array<double, 3> makeArrayFromCoordinates();
};
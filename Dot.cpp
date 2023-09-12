#include "Dot.h"
#include "MathVector.h"
bool Dot::areInOnePLane(vector <Dot> Dots)
{
    vector<vector<double>> matr(Dots.size());
    for (size_t i = 0; i < size(Dots); ++i)
        for (size_t j = 0; j < 3; ++j)
            matr[i].push_back(Dots[i].makeArrayFromCoordinates()[j]);
    Matrix m(matr);
    return m.Matrix::rank() != 3;
}

double Dot::distanceBetweenDots(Dot A, Dot B)
{
    return MathVector::moduleOfVector(MathVector(A, B));
}

std::array<double, 3> Dot::makeArrayFromCoordinates()
{
    return { this->x, this->y, this->z };
}
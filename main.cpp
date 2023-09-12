#include "PirsonCheck.h"
#include "Matrix.h"
#include "MathVector.h"
#include "Dot.h"
#include "Line.h"
#include "Plane.h"
#include "EquationSystem.h"
#include "ProbabilityTheory.h"
#include "BinomialDistribution.h"
#include "NormalDistribution.h"
#include "Correlation.h"

int main()
{
    setlocale(LC_ALL, "russian");
    Matrix matrix(Matrix::fillMatrix());
    std::cout << matrix.rank() << '\n';
    matrix.print();
    if (Matrix::determinant(matrix).has_value())
        std::cout << "determinant is " << Matrix::determinant(matrix).value() << '\n';
    if (matrix.inverseMatrix().has_value())
    matrix.inverseMatrix().value().print();
    return 0;
}
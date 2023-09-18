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
    EquationSystem sys(matrix.matrix);
    Matrix solution(sys.solveSystemByInversedMatrix().value());
    std::cout << "Solution:\n";
    solution.print();
}
#include "Matrix.h"
#include "EquationSystem.h"

EquationSystem::EquationSystem(vector<vector<double>>& system) : 
    rightEquationsSide(vector<vector<double>>(system.size(), vector<double>(1))), system(system)
{
    this->equationCount = system.size();
    setRightEquationsSide(system); //take off last numbers in rows
}

void EquationSystem::setVariableMatrix()
{
    this->variablesMatrix = this->system;
    for (vector<double> row : this->variablesMatrix.matrix)
        row.pop_back();
}
std::optional<Matrix> EquationSystem::solveSystemByInversedMatrix()
{
    std::optional<Matrix> inversedMatrix = this->variablesMatrix.inverseMatrix();
    if (inversedMatrix.has_value()) // system has a solution
        return inversedMatrix.value() * this->rightEquationsSide; // Matrix Multiplication: X = A^(-1) * B
    else // system doesn't have a solution
        return std::nullopt; // return nothing
}

void EquationSystem::setRightEquationsSide(vector<vector<double>>& system)
{
    for (size_t i = 0; i < this->equationCount; ++i)
        this->rightEquationsSide[i][0] = this->system[i].back();
}

bool EquationSystem::isMatrixConsistent()
{
    return this->system.rank() == this->variablesMatrix.rank();
}
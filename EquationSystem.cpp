#include "EquationSystem.h"
    EquationSystem::EquationSystem(vector<vector<double>>& system)
        : variablesKoefficientTable([&system]() {
        vector<vector<double>> table;
        for (vector<double>& row : system)
            table.push_back(row);
        return table;
            }())
    {
        setRightEquationsSide(system); // set numbers which stands in rightside to "="
    }

    std::optional<Matrix> EquationSystem::solveSystemByInversedMatrix()
    {
        if (this->variablesKoefficientTable.inverseMatrix().has_value()) // system have solution
        {
            Matrix invesedMatrix = this->variablesKoefficientTable.inverseMatrix().value();
            return invesedMatrix * this->rightEquationsSide; //Matrix Multiplication: X = A^(-1) * B
        }
        else // system doesnt have solution
            return std::nullopt; // return hothing
    }

    void EquationSystem::setRightEquationsSide(vector<vector<double>>& system)
    {
        for (vector<double>& row : system) {
            this->rightEquationsSide.matrix[0].push_back(row.back());
            row.pop_back();
        }
    }
#pragma once
#include "Matrix.h"
class EquationSystem
{
public:
	EquationSystem(vector<vector<double>>&);
	std::optional<Matrix> solveSystemByInversedMatrix();
private:
	Matrix variablesKoefficientTable;
	Matrix rightEquationsSide;
	void setRightEquationsSide(vector<vector<double>>&);
};
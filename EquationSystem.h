#pragma once
#include "Matrix.h"
class EquationSystem : public Matrix
{
public:
	EquationSystem(vector<vector<double>>&);
	std::optional<Matrix> solveSystemByInversedMatrix();
private:
	unsigned equationCount;
	Matrix system;
	Matrix variablesMatrix;
	Matrix rightEquationsSide;
	void setVariableMatrix();
	bool isMatrixConsistent();
	void setRightEquationsSide(vector<vector<double>>&);
};
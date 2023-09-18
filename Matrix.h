#pragma once
#include <vector>
#include <optional>
#include <iostream>
using std::vector;
class Matrix
{
public:
	Matrix() {};
	Matrix(const vector <vector<double>>);
	virtual void print();
	static vector<vector<double>> fillMatrix();
	int rank();
	void transpose();
	std::optional<Matrix> inverseMatrix();
	static std::optional<double> determinant(const Matrix&);
	Matrix matrixPow(Matrix, size_t);

	const std::vector<double>& operator[] (size_t rowIndex) const;
	std::vector<double>& operator[] (size_t rowIndex);
	Matrix operator* (const Matrix& M2);
	Matrix operator*= (double number);

	vector<vector< double >> matrix;
	size_t row_count;
	size_t col_count;
	
private:
	static bool isMatrixSquare(const Matrix& matrix);
	static bool isMatrixRectangle(const Matrix& Matrix);
	double minor(int, int);
};
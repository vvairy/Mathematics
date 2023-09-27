#pragma once
#include <vector>
#include <optional>
#include <iostream>
using std::vector;
class Matrix
{
public:
//constructors
	Matrix() {};
	Matrix(const vector <vector<double>>);

//methods
	virtual void print();
	static Matrix fillMatrix();
	int rank();
	void transpose();
	std::optional<Matrix> inverseMatrix();
	static std::optional<double> determinant(const Matrix&);

//operators
	const std::vector<double>& operator[] (size_t rowIndex) const;
	std::vector<double>& operator[] (size_t rowIndex);
	Matrix operator* (const Matrix& anotherMatrix);
	Matrix operator*= (const Matrix& anotherMatrix);
	Matrix operator*= (double number);
	Matrix operator+= (Matrix& anotherMatrix);
	Matrix operator+ (Matrix& anotherMatrix);

//matrix
	vector<vector<double>> matrix;
	size_t rowCount() const;
	size_t colCount() const;
	
private:
	Matrix(size_t row_len, size_t col_len);
	static bool isMatrixSquare(const Matrix& matrix);
	static bool isMatrixRectangle(const Matrix& Matrix);
	double minor(int, int);
};
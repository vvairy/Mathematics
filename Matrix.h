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
	void transpositione();
	std::optional<Matrix> inverseMatrix();
	const std::vector<double>& operator[] (size_t rowIndex) const;
	std::vector<double>& operator[] (size_t rowIndex);
	static std::optional<double> determinant(const Matrix&);
	Matrix matrixPow(Matrix, size_t);
	double minor(int, int);

	

	vector<vector< double >> matrix;
	size_t row_len;
	size_t col_len;
protected:
	friend Matrix operator*= (Matrix& M, double number);
	friend Matrix operator* (const Matrix& M1, const Matrix& M2);
private:
	static bool isMatrixSquare(const Matrix& matrix);
	static bool isMatrixRectangle(const Matrix& Matrix);
};
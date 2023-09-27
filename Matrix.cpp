#include "Matrix.h"
Matrix::Matrix(const vector<vector<double>> matrix) : matrix(matrix) {}
Matrix::Matrix(size_t row_len, size_t col_len) : matrix(row_len, vector<double>(col_len)) {}

void Matrix::print()
{
    for (size_t i = 0; i < this->rowCount(); ++i)
    {
        for (size_t j = 0; j < this->colCount(); ++j)
            std::cout << this->matrix[i][j] << " ";
        std::cout << std::endl;
    }
}

Matrix Matrix::fillMatrix() 
{
    size_t row_count, col_count;
    std::cout << "Write row count:\n"; std::cin >> row_count;
    std::cout << "Write column count:\n"; std::cin >> col_count;
    vector<vector<double>> matrix(row_count, vector<double>(col_count));
    for (size_t i = 0; i < row_count; i++)
        for (size_t j = 0; j < col_count; j++) {
            double el;
            std::cout << "Write el of matrix " << i + 1 << " " << j + 1 << " - ";
            while (!(std::cin >> el)) { // checking success of reading input
                std::cout << "Incorrect input. Try write with index " << i + 1 << " " << j + 1 << " again: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip remaining part of string
            }
            matrix[i][j] = el;
        }
    return matrix;
}

int Matrix::rank()
{
    Matrix copyMatrix(*this);
    int rank = 0;
    for (int i = 0; i < copyMatrix.colCount(); i++)
    {
        int nonZeroRow = rank;
        while (nonZeroRow < copyMatrix.rowCount() && copyMatrix[nonZeroRow][i] == 0)
            nonZeroRow++;
        if (nonZeroRow == this->rowCount()) //if column is fully zero - skip to next iteration
            continue;
        rank++;
        std::swap(copyMatrix[rank - 1], copyMatrix[nonZeroRow]);
        for (int j = rank; j < this->rowCount(); j++)
        {
            int factor = copyMatrix[j][i] / copyMatrix[rank - 1][i];
            for (int k = i; k < copyMatrix.colCount(); k++)
                copyMatrix[j][k] -= factor * copyMatrix[rank - 1][k];
        }
    }
    return rank;
}

void Matrix::transpose() //rotate in 90 degrees to right side
{
    for (size_t i = 0; i < this->rowCount(); i++)
        for (size_t j = i; j < this->colCount(); j++)
            std::swap(this->matrix[i][j], this->matrix[j][i]); 
}

std::optional<Matrix> Matrix::inverseMatrix()
{
    if (!isMatrixSquare(this->matrix)) //only square matrixes can be inersed
        return std::nullopt;

    double det = determinant(this->matrix).value_or(0);
    if (!det) // if det is 0 matrix has no inverse itself
        return std::nullopt;

    Matrix inversedMatrix(this->rowCount(), this->colCount());
    for (int i = 0; i < this->rowCount(); ++i)
        for (int j = 0; j < this->rowCount(); ++j)
            inversedMatrix[i][j] = ::pow(-1, i + j) * minor(i, j) / det;

    inversedMatrix.transpose();
    return matrix;
}

const std::vector<double>& Matrix::operator[] (size_t rowIndex) const
{
    if (rowIndex >= this->matrix.size())
        throw std::out_of_range("Row index out of range");
    return this->matrix[rowIndex];
}

std::vector<double>& Matrix::operator[] (size_t rowIndex)
{
    if (rowIndex >= rowCount())
        throw std::out_of_range("Row index out of range");
    return this->matrix[rowIndex];
}

Matrix Matrix::operator+= (Matrix& anotherMatrix)
{
    if (this->matrix.size() != anotherMatrix.matrix.size() or (*this)[0].size() != anotherMatrix[0].size())
        throw std::exception("non-summariable matrixes");

    for (size_t i = 0; i < anotherMatrix.matrix.size(); ++i)
        for (size_t j = 0; j < anotherMatrix[0].size(); ++j)
            (*this)[i][j] += anotherMatrix[i][j];
    return *this;
}

Matrix Matrix::operator+ (Matrix& anotherMatrix)
{
    if (this->matrix.size() != anotherMatrix.matrix.size() or (*this)[0].size() != anotherMatrix[0].size())
        throw std::exception("non-summariable matrixes");

    Matrix newMatrix(this->rowCount(), this->colCount());
    for (size_t i = 0; i < anotherMatrix.matrix.size(); ++i)
        for (size_t j = 0; j < anotherMatrix[0].size(); ++j)
            newMatrix[i][j] = (*this)[i][j] + anotherMatrix[i][j];
    return newMatrix;
}

std::optional<double> Matrix::determinant(const Matrix& matrix) //https://en.wikipedia.org/wiki/Determinant
{
    if (!isMatrixSquare(matrix))
    {
        std::cout << "Not square Matrix"; return std::nullopt;
    }

    if (matrix.rowCount() == 1)
        return matrix[0][0];

    double det = 0;
    for (int idx = 0; idx < matrix.rowCount(); idx++)
    {
        vector<vector<double>> Newmatrix(matrix.rowCount() - 1);
        for (size_t i = 1; i < matrix.rowCount(); i++)
            for (size_t j = 0; j < matrix.colCount(); j++)
                if (j != idx)
                    Newmatrix[i - 1].push_back(matrix[i][j]);
        det += ::pow(-1, idx) * matrix[0][idx] * determinant(Newmatrix).value(); //recursively calculate the determinant
        Newmatrix.clear();
    }
    return det;
}

Matrix Matrix::operator* (const Matrix& anotherMatrix) //https://en.wikipedia.org/wiki/Matrix_multiplication
{
    if (this->colCount() != anotherMatrix.rowCount())
        throw std::exception("Non-multiplyable matrixes");

    vector<vector<double>> NewMatrix(this->rowCount(), vector<double>(anotherMatrix.colCount()));
    for (size_t i = 0; i < this->rowCount(); i++)
        for (size_t j = 0; j < anotherMatrix.colCount(); j++)
        {
            double el = 0;
            for (size_t idx = 0; idx < colCount(); idx++)
                el += (*this)[i][idx] * anotherMatrix[idx][j];
            NewMatrix[i][j] = el;
        }
    return NewMatrix;
}

Matrix Matrix::operator*= (const Matrix& anotherMatrix) //https://en.wikipedia.org/wiki/Matrix_multiplication
{
    if (this->colCount() != anotherMatrix.rowCount())
        throw std::exception("Non-multiplyable matrixes");

    vector<vector<double>> NewMatrix(this->rowCount(), vector<double>(anotherMatrix.colCount()));
    for (size_t i = 0; i < this->rowCount(); i++)
        for (size_t j = 0; j < anotherMatrix.colCount(); j++)
        {
            double el = 0;
            for (size_t idx = 0; idx < colCount(); idx++)
                el += (*this)[i][idx] * anotherMatrix[idx][j];
            (*this)[i][j] = el;
        }
    return (*this);
}

Matrix Matrix::operator*= (double number) // multipling every matrix number to number
{
    for (vector<double> row : this->matrix)
        for (double el : row)
            el *= number;
    return *this;
}

bool Matrix::isMatrixSquare(const Matrix& matrix) // is row len equal column len
{
    return matrix.rowCount() == matrix.colCount() && isMatrixRectangle(matrix);
}

bool Matrix::isMatrixRectangle(const Matrix& matrix) //are all rows have the same len (so columns too)
{
    for (size_t i = 1; i < matrix.rowCount(); i++)
        if (matrix.colCount() != matrix[i].size()) //every row and col should be the same size
            return false;
    return true;
}

double Matrix::minor(int row_idx, int col_idx)
{
    vector<vector<double>> smallMatrix(rowCount() - 1, vector<double>(rowCount() - 1));
    for (size_t i = 0, m = 0; i < rowCount(); ++i)
        if (i != row_idx)
        {
            for (size_t j = 0, n = 0; j < colCount(); ++j)
                if (j != col_idx)
                {
                    smallMatrix[m][n] = matrix[i][j];
                    ++n;
                }
            ++m;
        }
    return determinant(smallMatrix).value();
}

size_t Matrix::rowCount() const
{
    return this->matrix.size();
}

size_t Matrix::colCount() const
{
    return this->matrix[0].size();
}

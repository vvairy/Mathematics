#include "Matrix.h"
Matrix::Matrix(const vector<vector<double>> matrix) : matrix(matrix) 
{
    this->row_count = matrix.size();
    this->col_count = matrix[0].size();
}

size_t row_count;
size_t col_count;

void Matrix::print()
{
    for (size_t i = 0; i < this->row_count; ++i)
    {
        for (size_t j = 0; j < this->col_count; ++j)
            std::cout << this->matrix[i][j] << " ";
        std::cout << std::endl;
    }
}

vector<vector<double>> Matrix::fillMatrix() 
{
    double row_count, col_count;
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
    for (int i = 0; i < copyMatrix.col_count; i++)
    {
        int nonZeroRow = rank;
        while (nonZeroRow < copyMatrix.row_count && copyMatrix[nonZeroRow][i] == 0)
            nonZeroRow++;
        if (nonZeroRow == this->row_count) //if column is fully zero - skip to next iteration
            continue;
        rank++;
        std::swap(copyMatrix[rank - 1], copyMatrix[nonZeroRow]);
        for (int j = rank; j < this->row_count; j++)
        {
            int factor = copyMatrix[j][i] / copyMatrix[rank - 1][i];
            for (int k = i; k < copyMatrix.col_count; k++)
                copyMatrix[j][k] -= factor * copyMatrix[rank - 1][k];
        }
    }
    return rank;
}

void Matrix::transpose() //rotate in 90 degrees to left side
{
    for (size_t i = 0; i < this->row_count; i++)
        for (size_t j = i; j < this->col_count; j++)
            std::swap(this->matrix[i][j], this->matrix[j][i]); 
}

std::optional<Matrix> Matrix::inverseMatrix()
{
    if (!isMatrixSquare(this->matrix)) //only square matrixes can be inersed
        return std::nullopt;
    double det = determinant(this->matrix).value_or(0);
    if (!det) // if det is 0 matrix has no inverse itself
        return std::nullopt;
    vector<vector<double>> inversedMatrix(this->row_count, vector<double>(this->col_count));

    for (int i = 0; i < this->row_count; ++i)
        for (int j = 0; j < this->row_count; ++j)
            inversedMatrix[i][j] = ::pow(-1, i + j) * minor(i, j) / det;

    Matrix matrix(inversedMatrix); matrix.transpose();
    return matrix;
}

const std::vector<double>& Matrix::operator[] (size_t rowIndex) const
{
    if (rowIndex >= row_count)
        throw std::out_of_range("Row index out of range");
    return this->matrix[rowIndex];
}

std::vector<double>& Matrix::operator[] (size_t rowIndex)
{
    if (rowIndex >= row_count)
        throw std::out_of_range("Row index out of range");
    return this->matrix[rowIndex];
}

std::optional<double> Matrix::determinant(const Matrix& matrix) //https://en.wikipedia.org/wiki/Determinant
{
    if (!isMatrixSquare(matrix))
    {
        std::cout << "Not square Matrix"; return std::nullopt;
    }
    if (matrix.row_count == 1)
        return matrix[0][0];
    double det = 0;
    for (int idx = 0; idx < matrix.row_count; idx++)
    {
        vector<vector<double>> Newmatrix(matrix.row_count - 1);
        for (size_t i = 1; i < matrix.row_count; i++)
            for (size_t j = 0; j < matrix.col_count; j++)
                if (j != idx)
                    Newmatrix[i - 1].push_back(matrix[i][j]);
        det += ::pow(-1, idx) * matrix[0][idx] * determinant(Newmatrix).value(); //recursively calculate the determinant
        Newmatrix.clear();
    }
    return det;
}

Matrix Matrix::operator* (const Matrix& anotherMatrix) //https://en.wikipedia.org/wiki/Matrix_multiplication
{
    if (this->col_count != anotherMatrix.row_count)
        throw std::exception("Non-multiplyable matrixes");
    vector<vector<double>> NewMatrix(this->row_count, vector<double>(anotherMatrix.col_count));
    for (size_t i = 0; i < this->row_count; i++)
        for (size_t j = 0; j < anotherMatrix.col_count; j++)
        {
            double el = 0;
            for (size_t idx = 0; idx < col_count; idx++)
                el += (*this)[i][idx] * anotherMatrix[idx][j];
            NewMatrix[i][j] = el;
        }
    return NewMatrix;
}

Matrix Matrix::matrixPow(Matrix matrix, size_t number)
{
    if (number == 0)
        return matrix;
    return matrix * matrixPow(matrix, number - 1);
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
    return matrix.row_count == matrix.col_count && isMatrixRectangle(matrix);
}

bool Matrix::isMatrixRectangle(const Matrix& matrix) //are all rows have the same len (so columns too)
{
    for (size_t i = 1; i < matrix.row_count; i++)
        if (matrix.col_count != matrix[i].size()) //every row and col should be the same size
            return false;
    return true;
}

double Matrix::minor(int row_idx, int col_idx)
{
    vector<vector<double>> smallMatrix(row_count - 1, vector<double>(row_count - 1));
    for (size_t i = 0, m = 0; i < row_count; ++i)
        if (i != row_idx)
        {
            for (size_t j = 0, n = 0; j < col_count; ++j)
                if (j != col_idx)
                {
                    smallMatrix[m][n] = matrix[i][j];
                    ++n;
                }
            ++m;
        }
    return determinant(smallMatrix).value();
}

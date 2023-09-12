#include "Matrix.h"
Matrix::Matrix(const vector<vector<double>> matrix) : matrix(matrix) 
{
    this->row_len = matrix.size();
    this->col_len = matrix[0].size();
}

size_t row_len;
size_t col_len;
void Matrix::print()
{
    for (size_t i = 0; i < this->row_len; ++i)
    {
        for (size_t j = 0; j < this->col_len; ++j)
            std::cout << this->matrix[i][j] << " ";
        std::cout << std::endl;
    }
}
vector<vector<double>> Matrix::fillMatrix() 
{
    double row_len, col_len;
    std::cout << "Write row len:\n"; std::cin >> row_len;
    std::cout << "Write colum len:\n"; std::cin >> col_len;
    vector<vector<double>> matrix(row_len, vector<double>(col_len));
    for (size_t i = 0; i < row_len; i++)
        for (size_t j = 0; j < col_len; j++) {
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
    for (int i = 0; i < copyMatrix.col_len; i++)
    {
        int nonZeroRow = rank;
        while (nonZeroRow < copyMatrix.row_len && copyMatrix[nonZeroRow][i] == 0)
            nonZeroRow++;
        if (nonZeroRow == this->row_len) //if column is fully zero - skip to next iteration
            continue;
        rank++;
        std::swap(copyMatrix[rank - 1], copyMatrix[nonZeroRow]);
        for (int j = rank; j < this->row_len; j++)
        {
            int factor = copyMatrix[j][i] / copyMatrix[rank - 1][i];
            for (int k = i; k < copyMatrix.col_len; k++)
                copyMatrix[j][k] -= factor * copyMatrix[rank - 1][k];
        }
    }
    return rank;
}

void Matrix::transpositione() //rotate in 90 degrees to left side
{
    for (size_t i = 0; i < this->row_len; i++)
        for (size_t j = i; j < this->matrix[0].size(); j++)
            std::swap(this->matrix[i][j], this->matrix[j][i]); 
}

std::optional<Matrix> Matrix::inverseMatrix()
{
    if (!isMatrixSquare(this->matrix)) //only square matrixes can be inersed
        return std::nullopt;
    double det = determinant(this->matrix).value_or(0);
    if (!det) // if det is 0 matrix has no inverse itself
        return std::nullopt;
    vector<vector<double>> inversedMatrix(this->row_len, vector<double>(this->col_len));
    this->print();
    std::cout << std::endl;
    for (int i = 0; i < this->row_len; ++i)
        for (int j = 0; j < this->row_len; ++j)
        {
            inversedMatrix[i][j] = ::pow(-1, i + j) * minor(i, j) / det;
        }
    Matrix matrix(inversedMatrix); matrix.transpositione();
    return matrix;
}

const std::vector<double>& Matrix::operator[] (size_t rowIndex) const
{
    if (rowIndex >= row_len)
        throw std::out_of_range("Row index out of range");
    return this->matrix[rowIndex];
}

std::vector<double>& Matrix::operator[] (size_t rowIndex)
{
    if (rowIndex >= row_len)
        throw std::out_of_range("Row index out of range");
    return this->matrix[rowIndex];
}

std::optional<double> Matrix::determinant(const Matrix& matrix) //https://en.wikipedia.org/wiki/Determinant
{
    if (!isMatrixSquare(matrix))
    {
        std::cout << "Not square Matrix"; return std::nullopt;
    }
    if (matrix.row_len == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    double det = 0;
    for (int idx = 0; idx < matrix.row_len; idx++)
    {
        vector<vector<double>> Newmatrix(matrix.row_len - 1);
        for (size_t i = 1; i < matrix.row_len; i++)
            for (size_t j = 0; j < matrix.col_len; j++)
                if (j != idx)
                    Newmatrix[i - 1].push_back(matrix[i][j]);
        det += ::pow(-1, idx) * matrix[0][idx] * determinant(Newmatrix).value(); //recursively calculate the determinant
        Newmatrix.clear();
    }
    return det;
}

Matrix operator* (const Matrix& M1, const Matrix& M2) //https://en.wikipedia.org/wiki/Matrix_multiplication
{
    if (M1.row_len != M2.col_len)
        throw std::exception("Non-multiplyable matrixes");
    vector<vector<double>> NewMatrix(M1.row_len, vector<double>(M2.col_len));
    for (size_t i = 0; i < M1.row_len; i++)
        for (size_t j = 0; j < M2.col_len; j++)
        {
            double el = 0;
            for (size_t idx = 0; idx < col_len; idx++)
                el += M1[i][idx] * M2[idx][j];
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

Matrix operator*= (Matrix& M, double number) // multipling every matrix number to number
{
    for (vector<double> row : M.matrix)
        for (double el : row)
            el *= number;
    return M;
}


bool Matrix::isMatrixSquare(const Matrix& matrix) // is row len equal column len
{
    return matrix.row_len == matrix.col_len && isMatrixRectangle(matrix);
}

bool Matrix::isMatrixRectangle(const Matrix& matrix) //are all rows have the same len (so columns too)
{
    for (size_t i = 1; i < matrix.row_len; i++)
        if (matrix.col_len != matrix[i].size()) //every row and col should be the same size
            return false;
    return true;
}

double Matrix::minor(int row_idx, int col_idx)
{
    vector<vector<double>> smallMatrix(row_len - 1, vector<double>(row_len - 1));
    for (size_t i = 0, m = 0; i < row_len; ++i)
        if (i != row_idx)
        {
            for (size_t j = 0, n = 0; j < col_len; ++j)
                if (j != col_idx)
                {
                    smallMatrix[m][n] = matrix[i][j];
                    ++n;
                }
            ++m;
        }
    return determinant(smallMatrix).value();
}

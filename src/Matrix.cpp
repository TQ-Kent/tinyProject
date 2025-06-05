#include "../include/Matrix.h"
#include "../include/Vector.h"
#include <iostream>
#include <Eigen/Dense>

using namespace std;

// Constructor
Matrix::Matrix(int numRows, int numCols): mNumRows(numRows), mNumCols(numCols) {
    mData = new double*[mNumRows];
    for(int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols]{};
    }
}

Matrix::Matrix(const Matrix& other): mNumRows(other.mNumRows), mNumCols(other.mNumCols){
    mData = new double*[mNumRows];
    for(int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols]{};
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = other.mData[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; ++i) {
        delete[] mData[i];
    }
    delete[] mData;
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        // Clean up old memory
        for (int i = 0; i < mNumRows; ++i)
            delete[] mData[i];
        delete[] mData;

        // Allocate and copy
        mNumRows = other.mNumRows;
        mNumCols = other.mNumCols;
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; ++i) {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; ++j)
                mData[i][j] = other.mData[i][j];
        }
    }
    return *this;
}

//Unary operators
Matrix Matrix::operator+() const {
    return *this;
}

Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = -mData[i][j];
        }
    }
    return result;
}

// Binary operators
Matrix Matrix::operator+ (Matrix const& other) const {
    if (mNumCols != other.mNumCols && mNumRows != other.mNumRows)
        throw runtime_error("Matrix sizes do not match for addition.");
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] + other.mData[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator- (Matrix const& other) const {
    if (mNumCols != other.mNumCols && mNumRows != other.mNumRows)
        throw runtime_error("Matrix sizes do not match for subtraction");
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] - other.mData[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator* (Matrix const& other) const {
    if (mNumCols != other.mNumRows)
        throw runtime_error("Matrix sizes do not match for multiplication");
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < other.mNumCols; j++) {
            for (int k = 0; k < mNumCols; k++) {
                result.mData[i][j] += mData[i][k] * other.mData[k][j];
            }
        }
    }
    return result;
}

// Scalar multiplication
Matrix Matrix::operator* (double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] * scalar;
        }
    }
    return result;
}

// Matrix-Vector multiplication
Vector Matrix::operator* (Vector& other) const {
    if (mNumCols != other.size()) {
        throw std::runtime_error("Matrix and vector sizes are incompatible for multiplication.");
    }

    Vector result(mNumRows);

    for (int i = 0; i < mNumRows; ++i) {
        double sum = 0.0;
        for (int j = 0; j < mNumCols; ++j) {
            sum += mData[i][j] * other[j];
        }
        result[i] = sum;
    }

    return result;
}

// Overloaded index operators
double* Matrix::operator[](int index) {
    if (index < 0 || index >= mNumRows)
        throw out_of_range("Index out of range in [] operator.");
    return mData[index];
}
const double* Matrix::operator[](int index) const {
    if (index < 0 || index >= mNumRows)
        throw out_of_range("Index out of range in [] operator.");
    return mData[index];
}

double* Matrix::operator()(int index) {
    if (index < 1 || index > mNumRows)
        throw out_of_range("Index out of range in [] operator.");
    return mData[index - 1];
}
const double* Matrix::operator()(int index) const {
    if (index < 1 || index > mNumRows)
        throw out_of_range("Index out of range in [] operator.");
    return mData[index - 1];
}

// Utility
void Matrix::size() const {
    cout << "Size: (" << mNumRows << "," << mNumCols << ")" << endl;
};
void Matrix::print() const {
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            cout << mData[i][j] << "\t";
        }
        cout << endl;
    }
}
void Matrix::swapRows(int rIndex1, int rIndex2) {
    if (rIndex1 < 0 || rIndex2 < 0 || rIndex1 >= mNumRows || rIndex2 >= mNumRows) {
        throw std::out_of_range("Row index out of bounds");
    }

    for (int i = 0; i < mNumCols; i++) {
        swap(mData[rIndex1][i], mData[rIndex2][i]);
    }
}

// Matrix function
double Matrix::det() const{
    if (mNumRows != mNumCols)
        throw runtime_error("Matrix sizes do not match for calculating determinant");

    if (mNumRows == 1) return mData[0][0];
    if (mNumRows == 2) return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];

    double det = 0.0;
    for (int i = 0; i < mNumRows; i++) {
        Matrix minor = getMinor(0, i);
        det += ((i % 2 == 0) ? 1 : -1) * mData[0][i] * minor.det();
    }
    return det;
}   

Matrix Matrix::getMinor(int row, int col) const{
    Matrix result(mNumRows - 1, mNumCols -1);

    for(int i = 0, minorRow = 0; i < mNumRows; i++) {
        if (i == row) continue;
        for (int j = 0, minorCol = 0; j < mNumCols; j++) {
            if (j == col) continue;
            result.mData[minorRow][minorCol++] = mData[i][j];
        }
        minorRow++;
    }

    return result;
}

Matrix Matrix::inverse() const{
    if (mNumRows != mNumCols)
        throw runtime_error("Matrix sizes do not match for calculating inverse");

    Matrix result(mNumRows, mNumCols);

    // Step 1: Determinant
    double determinant = det();

    // Step 2: Calculating the coffactors for each element
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumRows; j++) {
            result.mData[i][j] = (((i + j) % 2 == 0) ? 1 : -1) * getMinor(i, j).det();
        }
    }
    // Step 3: Transpose the matrix
    result = result.transpose();

    // Step 3: Calculating the inverse
    return result * (1/determinant);
}

Matrix Matrix::transpose() const{
    Matrix result(mNumCols, mNumRows);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[j][i] = mData[i][j];
        }
    }
    return result;
}   

Matrix Matrix::pseudo_inverse() const {
    // Convert your Matrix to an Eigen::MatrixXd
    Eigen::MatrixXd eigenMat(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            eigenMat(i, j) = mData[i][j];
        }
    }

    // Compute the pseudoinverse using SVD
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(eigenMat, Eigen::ComputeThinU | Eigen::ComputeThinV);
    const double epsilon = 1e-10; // Tolerance for small singular values

    Eigen::VectorXd singularValuesInv = svd.singularValues();
    for (int i = 0; i < singularValuesInv.size(); ++i) {
        if (singularValuesInv(i) > epsilon)
            singularValuesInv(i) = 1.0 / singularValuesInv(i);
        else
            singularValuesInv(i) = 0.0;
    }

    Eigen::MatrixXd pseudoInv = svd.matrixV() * singularValuesInv.asDiagonal() * svd.matrixU().transpose();

    // Convert the result back to your Matrix class
    Matrix result(pseudoInv.rows(), pseudoInv.cols());
    for (int i = 0; i < pseudoInv.rows(); ++i) {
        for (int j = 0; j < pseudoInv.cols(); ++j) {
            result[i][j] = pseudoInv(i, j);
        }
    }

    return result;
}
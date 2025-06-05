#pragma once

#include "Vector.h"

// 2) You are required develop a class of matrices called Matrix. It should include the features listed 
// below. Your class should have private members mNumRows and mNumCols that are integers 
// and store the number of rows and columns, and mData that is a pointer to a pointer to a data 
// element of matrix, which stores the address of the pointer to the first entry of the first row:
// - An overridden copy constructor that copies the variables mNumRows and mNumCols, 
// allocates memory for a new matrix, and copies the entries of the original matrix into the 
// new matrix.
// - A constructor that accepts two positive integers numRows and numCols as input, assigns
// these values to the class members mNumRows and mNumCols, allocates memory for a 
// matrix of size mNumRows by mNumCols, and initialises all entries to zero.
// - An overridden destructor that frees the memory that has been allocated to the matrix. 
// - Public methods for accessing the number of rows, and the number of columns.
// - An overloaded round bracket operator with one-based indexing for accessing the entries of 
// the matrix so that, provided i and j are valid indices for the matrix, A(i,j) may be used to 
// access mData[i-1][j-1].
// - Overloaded assignment, unary and binary operators to allow addition, subtraction and 
// multiplication of suitably sized matrices, vectors and scalars. You should use assert 
// statements to ensure the matrices and vectors are of the correct size.
// - A public method that computes the determinant of a given square matrix.
// - A public method that computes the inverse of a given square matrix.
// - A public method that computes the pseudo-inverse (Moore-Penrose inverse) of a given 
// matrix.

class Matrix
{
private:
    int mNumRows;
    int mNumCols;
    double** mData;
public:
    Matrix(int numRows = 0, int numCols = 0);
    Matrix(const Matrix& other);
    ~Matrix();

    // Assignment operator
    Matrix& operator=(const Matrix& other);

    //Unary operators
    Matrix operator+() const;
    Matrix operator-() const;

    // Binary operators
    Matrix operator+ (Matrix const& other) const;
    Matrix operator- (Matrix const& other) const;
    Matrix operator* (Matrix const& other) const;

    // Scalar multiplication
    Matrix operator* (double scalar) const;
    
    // Matrix-Vector multiplication
    Vector operator* (Vector& other) const;
    
    // Overloaded index operators
    double* operator[](int index);
    const double* operator[](int index) const;

    double* operator()(int index);
    const double* operator()(int index) const;

    // Utility
    void size() const;
    int nRows() {return mNumRows;}
    int nCols() {return mNumCols;}
    void print() const;
    void swapRows(int rIndex1, int rIndex2);

    // Matrix function
    double det() const;
    Matrix getMinor(int row, int col) const;
    Matrix inverse() const;
    Matrix transpose() const;
    Matrix pseudo_inverse() const;
};
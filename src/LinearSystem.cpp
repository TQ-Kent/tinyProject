#include "../include/LinearSystem.h"
#include "../include/Vector.h"
#include "../include/Matrix.h"
#include<iostream>
#include<cmath>

using namespace std;

// LinearSystem //
// Constructor
LinearSystem::LinearSystem(Matrix& A, Vector& b): mpA(A), mpb(b) {
    if (A.nRows() != A.nCols()) {
        throw std::runtime_error("Matrix must be square.");
    }
    if (A.nRows() != b.size()) {
        throw std::runtime_error("Matrix and vector sizes are incompatible.");
    }
    mSize = A.nRows();
}

// Destructor
LinearSystem::~LinearSystem() = default;

// Gaussian elimination
Vector LinearSystem::Solve() {
    Matrix A = mpA;
    Vector b = mpb;

    for (int i = 0; i < mSize; ++i) {
        // Partial pivoting
        int maxRow = i;
        for (int k = i+1; k < mSize; ++k) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        if (maxRow != i) {
            A.swapRows(i, maxRow);
            swap(b[i], b[maxRow]);
        }

        for (int k = i+1; k < mSize; ++k) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < mSize; ++j) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    // Back-substitution
    Vector x(mSize);
    for (int i = mSize-1; i >= 0; --i) {
        x[i] = b[i];
        for (int j = i+1; j < mSize; ++j) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    return x;
}

// PosSymLinSystem //
// Constructor
PosSymLinSystem::PosSymLinSystem(Matrix& A, Vector& b) : LinearSystem(A, b) {
    if (!isSymmetric(A)) {
        throw runtime_error("Matrix is not symmetric.");
    }
}

// Destructor
PosSymLinSystem::~PosSymLinSystem() = default;

// Check Symetric
bool PosSymLinSystem::isSymmetric(Matrix& A) {
    int n = A.nRows();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (A[i][j] != A[j][i]) {
                return false;
            }
        }
    }
    return true;
}

// Conjugate gradient
Vector PosSymLinSystem::Solve() {
    Matrix A = mpA;
    Vector b = mpb;

    Vector x(mSize); // initial guess x0 = 0
    Vector r = b - (A * x); // r0 = b - A*x0 = b
    Vector p = r;
    Vector Ap(mSize);

    double tol = 1e-10;
    int maxIter = mSize * 2;
    double alpha, beta, rs_old, rs_new;

    rs_old = r * r; // rᵗ * r

    for (int i = 0; i < maxIter; ++i) {
        Ap = A * p;
        alpha = rs_old / (p * Ap); // α = rᵗr / pᵗAp

        x = x + p * alpha; // x = x + αp
        r = r - Ap * alpha; // r = r - αAp

        rs_new = r * r;

        if (sqrt(rs_new) < tol)
            break;

        beta = rs_new / rs_old; // β = rₖ₊₁ᵗ * rₖ₊₁ / rₖᵗ * rₖ
        p = r + p * beta;

        rs_old = rs_new;
    }

    return x;
}

// GeneralLinSystem //
// Constructor
GeneralLinSystem::GeneralLinSystem(Matrix& A, Vector& b): mpA(A), mpb(b) {
    if (A.nRows() != b.size()) {
        throw std::runtime_error("Matrix and vector sizes are incompatible.");
    }
    mSize = A.nRows();
}
// Destructor
GeneralLinSystem::~GeneralLinSystem() = default;

// Moore-Penrose solution: x = A⁺ b
Vector GeneralLinSystem::SolveMoorePenrose() {
    Matrix A_pinv = mpA.pseudo_inverse();
    return A_pinv * mpb;
}

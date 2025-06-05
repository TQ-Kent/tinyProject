#pragma once

#include "Matrix.h"
#include "Vector.h"

// 3) You are required to develop a class called LinearSystem that may be used to solve linear 
// systems. Assuming the system is nonsingular, a linear system is defined by the size of the 
// linear system, a square matrix, and vector (representing the right-hand side), with the matrix 
// and vector being of compatible sizes. The data associated with this class may be specified 
// through an integer variable mSize, a pointer to a matrix mpA, and a pointer to the vector on the
// right-hand side of the linear system mpb. We suggest only allowing the user to set up a linear 
// system using a constructor that requires specification of the matrix and vector: the member
// mSize may then be determined from these two members. If you do not wish to provide a copy 
// constructor, then the automatically generated copy constructor should be overridden and made 
// private to prevent its use. As with the class of vectors, we recommend that use of the 
// automatically generated default constructor is prevented by providing a specialised constructor
// but no default constructor. A public method Solve should be written to solve this linear system 
// by Gaussian elimination with pivoting. This method should return a vector that contains the 
// solution of the linear system.
// Derive a class called PosSymLinSystem (or similar) from the class LinearSystem that may 
// be used for the solution of positive definite symmetric linear systems. Make the method Solve
// a virtual method of the class LinearSystem, and override this method in the class
// PosSymLinSystem so that it uses the conjugate gradient method for solving linear systems. If
// you declared LinearSystem member data as private, then this should now be declared protected.
// Your class PosSymLinSystem should perform a check that the matrix used is symmetric: testing
// that the matrix is positive definite would be rather difficult and so we don’t suggest performing
// a check for this property. Test your class using suitable examples.


class LinearSystem {
protected:
    int mSize;
    Matrix& mpA;
    Vector& mpb;

public:
    LinearSystem(Matrix& A, Vector& b);
    virtual ~LinearSystem();
    virtual Vector Solve(); // Gaussian elimination
private:
    LinearSystem() = delete;
    LinearSystem(const LinearSystem&) = delete;
};

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(Matrix& A, Vector& b);
    ~PosSymLinSystem();

    bool isSymmetric(Matrix& A);
    Vector Solve() override; // Conjugate gradient
};

class GeneralLinSystem {
private:
    int mSize;
    Matrix& mpA;
    Vector& mpb;
public:
    GeneralLinSystem(Matrix& A, Vector& b);
    ~GeneralLinSystem();

    Vector SolveMoorePenrose();
};
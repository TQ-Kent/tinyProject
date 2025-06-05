#pragma once

#include<iostream>

// 1) You are required to develop a class of matrices called Vector. It will include constructors and 
// destructors that handle memory management. It will overload the assignment, unary and binary 
// operators to allow addition, subtraction, and multiplication of vectors and scalars. The square 
// bracket operator will be overloaded for the vector class to provide a check that the index of the 
// array lies within the correct range, and the round bracket operator will be overloaded to allow 
// the entries of the vector to be accessed, indexing from 1 rather than from zero. The class should 
// have private members mSize (the size of the array) and mData that is a pointer to a data element 
// of array.

class Vector
{
private:
    int mSize;
    double* mData;

public:
    // Constructor and destructor
    Vector(int size = 0);
    Vector(const Vector& others); // Copy constructor
    ~Vector() {delete[] mData;}

    // Assignment operator
    Vector& operator=(const Vector& other);

    //Unary operators
    Vector operator+() const;
    Vector operator-() const;

    // Binary operators
    Vector operator+ (Vector const& other) const;
    Vector operator- (Vector const& other) const;
    double operator* (Vector const& other) const;

    // Scalar multiplication
    Vector operator* (double scalar) const;
    
    // Overloaded index operators
    double& operator[](int index);        // 0-based, with bounds check
    const double& operator[](int index) const;

    double& operator()(int index);        // 1-based
    const double& operator()(int index) const;

    // Utility
    int size() const;
    void print() const;
};

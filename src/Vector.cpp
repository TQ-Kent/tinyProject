#include "../include/Vector.h"
#include <iostream>

using namespace std;

// Constructor and destructor
Vector::Vector(int size): mSize(size), mData(new double[mSize]) {
    for (int i = 0; i < mSize; i++) {
        mData[i] = 0.0;
    }
}

Vector::Vector(const Vector& other): mSize(other.mSize), mData(new double[mSize]) {
    for (int i = 0; i < mSize; i++) {
        mData[i] = other.mData[i];
    }
}

// Assignment operator
Vector& Vector::operator=(const Vector& other) {
    if (this != &other)
    {
        // delete[] mData;
        mSize = other.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; i++) {
            mData[i] = other.mData[i];
        }
    }
    return *this;
}

//Unary operators
Vector Vector::operator+() const{
    return *this;
}

Vector Vector::operator-() const{
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = -mData[i];
    }
    return result;
}

// Binary operators

Vector Vector::operator+ (Vector const& other) const {
    if (mSize != other.mSize)
        throw runtime_error("Vector sizes do not match for addition.");
    Vector result(mSize);
    for(int i = 0; i < mSize; i++) {
        result[i] = mData[i] + other.mData[i];
    }
    return result;
}

Vector Vector::operator- (Vector const& other) const {
    if (mSize != other.mSize)
        throw runtime_error("Vector sizes do not match for addition.");
    Vector result(mSize);
    for(int i = 0; i < mSize; i++) {
        result[i] = mData[i] - other.mData[i];
    }
    return result;
}

// Dot product
double Vector::operator* (Vector const& other) const {
    if (mSize != other.mSize)
        throw runtime_error("Vector sizes do not match for addition.");
    double sum = 0.0;
    for(int i = 0; i < mSize; i++) {
        sum += mData[i] * other.mData[i];
    }
    return sum;
}

// Scalar multiplication
Vector Vector::operator* (double scalar) const {
    Vector result(mSize);
    for(int i = 0; i < mSize; i++) {
        result[i] = mData[i] * scalar;
    }
    return result;
}

// Overloaded index operators

// 0-based, with bounds check
double& Vector::operator[] (int index) {
    if (index < 0 || index >= mSize)
        throw out_of_range("Index out of range in [] operator.");
    return mData[index];
}
const double& Vector::operator[] (int index) const {
    if (index < 0 || index >= mSize)
        throw out_of_range("Index out of range in [] operator.");
    return mData[index];
}

// 1-based
double& Vector::operator() (int index) {
    if (index < 1 || index > mSize)
        throw out_of_range("Index out of range in [] operator.");
    return mData[index - 1];
}       
const double& Vector::operator() (int index) const {
    if (index < 1 || index > mSize)
        throw out_of_range("Index out of range in [] operator.");
    return mData[index - 1];
}

// Utility
int Vector::size() const {
    return mSize;
}
void Vector::print() const{
    for (int i = 0; i < mSize; i++) {
        cout << mData[i] << ' ';
    }
    cout << endl;
}
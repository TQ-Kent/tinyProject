# tinyProject

# Linear System Solver & CPU Performance Predictor

## Overview

This project is split into two main parts:

### Part A: Linear System Solver  
A custom C++ implementation of `Vector`, `Matrix`, and `LinearSystem` classes that support solving equations of the form **Ax = b**.

### Part B: Linear Regression for CPU Performance  
Using data from the [UCI Computer Hardware dataset](https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware), we apply linear regression to predict CPU performance based on hardware specs. Model training and evaluation are implemented using the matrix solver developed in Part A.

---

## Features

### Vector Class
- Manual memory management (constructors/destructors)
- Operator overloading for:
  - Vector + Vector
  - Vector - Vector
  - Vector * Scalar
- Square `[]` indexing (0-based) with bounds checking
- Round `()` indexing (1-based)

### Matrix Class
- Dynamic memory allocation with deep copy constructor
- Operator overloading for:
  - Matrix + Matrix
  - Matrix - Matrix
  - Matrix * Scalar
  - Matrix * Vector
  - Matrix * Matrix
- Determinant calculation
- Matrix inverse and Moore-Penrose pseudo-inverse
- Round `()` indexing (1-based) with assert checks

### LinearSystem Class
- Solves **Ax = b** using:
  - Gaussian Elimination with partial pivoting
- `PosSymLinSystem` subclass:
  - Uses the Conjugate Gradient method
  - Checks for matrix symmetry
- Supports square and non-square systems

### Linear Regression
- Implements:
    - **PRP = x1MYCT + x2MMIN + x3MMAX + x4CACH + x5CHMIN + x6CHMAX**
- Parameters are determined using matrix methods from Part A
- Dataset split: 80% training, 20% testing
- Evaluation metric: Root Mean Square Error (RMSE)

## Project Structure
```bash
project/
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
├── bin/
│   └── tinyProject.exe
├── data/
│   ├── Index
│   ├── machine.data
│   └── machine.names
├── include/
│   ├── eigen-3.4.0/
│   ├── LinearSystem.h
│   ├── Matrix.h
│   └── Vector.h
├── src/
│   ├── LinearSystem.cpp
│   ├── Matrix.cpp
│   └── Vector.cpp
├── README.md
├── tinyProject.cpp
└── tinyProject.pdf
```

## Getting Started

### Prerequisites
- Make sure you have the following installed:
    - VSCode
    - MSYS2 with ucrt64 environment
    - <kbd>g++</kbd> (installed via <kbd>pacman -S mingw-w64-ucrt-x86_64-gcc</kbd>)
    - <kbd>gdb</kbd> debugger (<kbd>pacman -S mingw-w64-ucrt-x86_64-gdb</kbd>)

### Build Instructions
 - Open tinyProject.cpp.
 - Press <kbd>F5</kbd> or go to Run > Start Debugging.

This uses launch.json and runs the tinyProject.exe directly from the bin/ folder.

## Contributors
| Name                    | ID        |
|-------------------------|-----------|
| Phan Nguyễn Thanh Quân  | 10423098  |
| Nguyễn Trung Hiếu       | 10423040  |
| Đặng Quốc An            | 10423001  |
#include "include/Vector.h"
#include "include/Matrix.h"
#include "include/LinearSystem.h"

// File parsing
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <random> // for std::shuffle
#include <algorithm> // for std::shuffle
#include <ctime> // for seeding randomness

#include <iostream>

using namespace std;

void parse_csv(const string& filename,
               Matrix& X_train, Vector& Y_train,
               Matrix& X_test, Vector& Y_test) {
    ifstream file(filename);
    string line;

    // Skip header
    if (!getline(file, line)) {
        throw runtime_error("File is empty or missing header");
    }

    vector<std::vector<double>> features;
    vector<double> targets;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 10) continue;

        try {
            vector<double> x_row;
            for (int i = 2; i <= 7; ++i) {
                x_row.push_back(stod(tokens[i]));
            }
            double prp = stod(tokens[8]);

            features.push_back(x_row);
            targets.push_back(prp);
        }
        catch (const invalid_argument&) {
            continue;
        }
    }

    std::cout << "Parsed " << features.size() << " rows." << std::endl;

    vector<pair<vector<double>, double>> data;
    for (size_t i = 0; i < features.size(); ++i) {
        data.emplace_back(features[i], targets[i]);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);

    size_t total = data.size();
    size_t train_size = static_cast<size_t>(total * 0.8);

    X_train = Matrix(train_size, 6);
    Y_train = Vector(train_size);
    X_test = Matrix(total - train_size, 6);
    Y_test = Vector(total - train_size);

    for (size_t i = 0; i < train_size; ++i) {
        for (int j = 0; j < 6; ++j) {
            X_train[i][j] = data[i].first[j];
        }
        Y_train[i] = data[i].second;
    }

    for (size_t i = train_size; i < total; ++i) {
        for (int j = 0; j < 6; ++j) {
            X_test[i - train_size][j] = data[i].first[j];
        }
        Y_test[i - train_size] = data[i].second;
    }
}

Vector solve_linear_regression(Matrix& X, Vector& Y) {
    // Step 1: Transpose X
    Matrix Xt = X.transpose();

    // Step 2: Xt * X
    Matrix XtX = Xt * X;

    // Step 3: (Xt * X)^-1
    Matrix XtX_inv = XtX.inverse();

    // Step 4: Xt * Y
    Vector XtY = Xt * Y;

    // Step 5: (XtX)^-1 * XtY
    Vector result = XtX_inv * XtY;

    return result;
}

Vector predict(Matrix& X, Vector& weights) {
    return X * weights;
}

double compute_rmse(const Vector& predicted, const Vector& actual) {
    if (predicted.size() != actual.size()) {
        throw runtime_error("Vectors must be the same size for RMSE calculation.");
    }

    double sum_squared_error = 0.0;
    for (int i = 0; i < predicted.size(); ++i) {
        double diff = predicted[i] - actual[i];
        sum_squared_error += diff * diff;
    }

    return sqrt(sum_squared_error / predicted.size());
}


int main()
{
    {// Part A
    // 1.
    /*
    try {
        // Create vectors
        Vector v1(3);        // Zero vector of size 3
        v1[0] = 1.0;
        v1[1] = 2.0;
        v1[2] = 3.0;

        cout << "v1: ";
        v1.print();

        // Copy constructor
        Vector v2(v1);
        cout << "v2 (copy of v1): ";
        v2.print();

        // Assignment operator
        Vector v3(3);
        v3 = v1;
        cout << "v3 (assigned from v1): ";
        v3.print();

        // Unary minus
        Vector v4 = -v1;
        cout << "-v1: ";
        v4.print();

        // Addition
        Vector v5 = v1 + v2;
        cout << "v1 + v2: ";
        v5.print();

        // Subtraction
        Vector v6 = v1 - v2;
        cout << "v1 - v2: ";
        v6.print();

        // Dot product
        double dot = v1 * v2;
        cout << "v1 . v2: " << dot << endl;

        // Scalar multiplication
        Vector v7 = v1 * 2.0;
        cout << "v1 * 2.0: ";
        v7.print();

        // Indexing
        cout << "v1[0] (0-based): " << v1[0] << endl;
        cout << "v1(1) (1-based): " << v1(1) << endl;

        // Bounds check (uncomment to test exception)
        // cout << v1[5] << endl;

    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
    */
    // 2.
    /*
    try {
        // Create a 2x2 matrix
        Matrix A(2, 2);
        A[0][0] = 4; A[0][1] = 7;
        A[1][0] = 2; A[1][1] = 6;

        cout << "Matrix A:\n";
        A.print();

        // Copy constructor
        Matrix B(A);
        cout << "Matrix B (copy of A):\n";
        B.print();

        // Addition
        Matrix C = A + B;
        cout << "A + B:\n";
        C.print();

        // Subtraction
        Matrix D = A - B;
        cout << "A - B:\n";
        D.print();

        // Scalar multiplication
        Matrix E = A * 2.0;
        cout << "A * 2.0:\n";
        E.print();

        // Determinant
        double detA = A.det();
        cout << "det(A) = " << detA << endl;

        // Inverse
        Matrix Ainv = A.inverse();
        cout << "A^-1:\n";
        Ainv.print();

        // Matrix * Matrix
        Matrix Identity = A * Ainv;
        cout << "A * A^-1 (should be identity):\n";
        Identity.print();

        // Matrix * Vector
        Vector v(2);
        v[0] = 1;
        v[1] = 2;

        Vector result = A * v;
        cout << "A * v:\n";
        result.print();

        // Transpose
        Matrix At = A.transpose();
        cout << "Transpose of A:\n";
        At.print();

        // Pseudo-inverse (non-square)
        Matrix M(2, 3);
        M[0][0] = 1; M[0][1] = 2; M[0][2] = 3;
        M[1][0] = 4; M[1][1] = 5; M[1][2] = 6;

        cout << "Matrix M (2x3):\n";
        M.print();

        Matrix M_pinv = M.pseudo_inverse();
        cout << "Pseudo-inverse of M:\n";
        M_pinv.print();

    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
    */
    // 3.
    /*
    try {
        // Test Gaussian Elimination
        Matrix A(3, 3);
        A[0][0] = 2; A[0][1] = 1; A[0][2] = -1;
        A[1][0] = -3; A[1][1] = -1; A[1][2] = 2;
        A[2][0] = -2; A[2][1] = 1; A[2][2] = 2;

        Vector b(3);
        b[0] = 8;
        b[1] = -11;
        b[2] = -3;

        LinearSystem system(A, b);
        Vector x = system.Solve();

        cout << "Solution (Gaussian): ";
        x.print(); // Expected: [2, 3, -1]

        // Test Conjugate Gradient
        Matrix M(3, 3);
        M[0][0] = 4; M[0][1] = 1; M[0][2] = 0;
        M[1][0] = 1; M[1][1] = 3; M[1][2] = 1;
        M[2][0] = 0; M[2][1] = 1; M[2][2] = 2;

        Vector d(3);
        d[0] = 1;
        d[1] = 2;
        d[2] = 3;

        PosSymLinSystem cgSystem(M, d);
        Vector cgResult = cgSystem.Solve();

        cout << "Solution (Conjugate Gradient): ";
        cgResult.print();

    } catch (exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
    */
    // 4.
    /*
    try {
        Matrix A(3, 2);  // 3x2 system
        A[0][0] = 1; A[0][1] = 2;
        A[1][0] = 3; A[1][1] = 4;
        A[2][0] = 5; A[2][1] = 6;

        Vector b(3);
        b[0] = 7; b[1] = 8; b[2] = 9;

        GeneralLinSystem sys(A, b);
        Vector x = sys.SolveMoorePenrose();
        x.print();
    }   catch (exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
    */
    }

    {//Part B
        Matrix X_train, X_test;
        Vector Y_train, Y_test;

        parse_csv("data/machine.data", X_train, Y_train, X_test, Y_test);

        // X_train.print();
        // Y_train.print();

        // Solve for weights
        Vector weights = solve_linear_regression(X_train, Y_train);

        // Print weights
        weights.print();

        Vector Y_pred = predict(X_test, weights);

        double rmse = compute_rmse(Y_pred, Y_test);
        cout << "RMSE on test set: " << rmse << std::endl;

        for (int i = 0; i < weights.size(); ++i) {
            cout << "Weight " << i << ": " << weights[i] << std::endl;
        }   
    }
    return 0;
}

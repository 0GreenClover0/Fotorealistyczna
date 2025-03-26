#pragma once
#include <string>
#include <vector>
#include "MathHelpers.h"

struct Vector;

struct Matrix
{

    Matrix(unsigned int r, unsigned int c)
    {
        this->rows = r;
        this->columns = c;

        for (int i = 0; i < r * c; i++)
            matrixArray.emplace_back(0);
    }

    // Use this to fill the matrix!
    float GetAt(unsigned int m, unsigned int n) const;
    void SetAt(float value, unsigned int m, unsigned int n);
    float Get(unsigned int i) const;
    void Set(float value, unsigned int i);

    unsigned int GetRows() const;
    unsigned int GetColumns() const;
    unsigned int GetVectorSize() const;

    std::string toString();
    Matrix operator +(const Matrix& m) const;
    Matrix operator -(const Matrix& m) const;
    bool operator ==(const Matrix& m);
    Matrix operator *(float f) const;
    Matrix operator *(const Matrix& m) const;
    Matrix operator !();                                            // Inverse matrix, way #1, requires square matrix
    Matrix inverse() const;                                         // Inverse matrix, way #2, requires square matrix
    Matrix identity() const;                                        // Requires square matrix
    Matrix transpose() const;
    float determinant() const;                                      // Requires square matrix
    float cofactorAt(unsigned int row, unsigned int col) const;

    /// Transformations ///
    // Call those on "vector" of Matrix type you want to translate, e.g. [1, 0, 0, 1]
    Matrix translate(const Vector& vector);
    Matrix rotate(Axis axis, float angle);                          // In RADIANS
    Matrix scale(const Vector& vector);

private:

    std::vector<float> matrixArray;                                 // Matrix m x n
    unsigned int rows, columns;

};

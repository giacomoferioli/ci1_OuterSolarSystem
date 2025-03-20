#include "Vector.hpp"
#include <cstring>
#include <initializer_list>
#include <math.h>

#ifndef MATRIX
#define MATRIX

#define ZERO_THRESHOLD 1e-9

class Matrix{
    private:
        double* data;

        double get(int i) const;
        void set(int i,double v);

        Matrix& cleanup();

    public:

        Matrix(const double* data = NULL);
        Matrix(const Matrix& base);
        Matrix(std::initializer_list<double> data);
        ~Matrix();

        double get(int i, int j) const;
        Matrix& set(int i, int j, double v);

        double det() const;
        Matrix transpose() const;
        Matrix cofactor() const;
        Matrix invert() const;

        Matrix& operator+=(const Matrix& b);
        Matrix& operator-=(const Matrix& b);
        Matrix& operator*=(const double b);
        Matrix& operator/=(const double b);

        Matrix& operator*=(const Matrix& b);
        
        Matrix operator+(const Matrix& b) const;
        Matrix operator-(const Matrix& b) const;
        Matrix operator*(const double b) const;
        Matrix operator/(const double b) const;

        Matrix operator*(const Matrix& b) const;
        Vec3 operator*(const Vec3& b) const;

        Matrix& operator=(const Matrix& b);
        Matrix& operator=(std::initializer_list<double> data);

        double* operator[](const int i);

        //friend Vec3 operator*(const Vec3& v, const Matrix& A);
        //friend Vec3 operator*=(Vec3& v, const Matrix& A);

        friend std::ostream& operator<<(std::ostream& os, const Matrix& v);
};

#endif
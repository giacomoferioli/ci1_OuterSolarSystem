#include <iostream>
#include <cstring>
#include <math.h>

#ifndef VEC3
#define VEC3

#define _x data[0]
#define _y data[1]
#define _z data[2]

class Vec3{
    private:
        double* data;

    public:
        static const Vec3 Zero,X,Y,Z;


        Vec3(double x = 0, double y = 0, double z = 0);
        Vec3(const double* data);
        Vec3(const Vec3& base);
        ~Vec3();

        double x() const { return data[0];};
        double y() const { return data[1];};
        double z() const { return data[2];};

        double get(int i) const;
        void set(int i, double v);

        Vec3 inverse() const;
        double dotprod(const Vec3& b) const;
        Vec3 crossprod(const Vec3& b) const;

        double mod() const;
        double mod2() const;
        Vec3 Normalize() const;

        Vec3& operator+=(const Vec3& b);
        Vec3& operator-=(const Vec3& b);
        Vec3& operator*=(const double b);
        Vec3& operator/=(const double b);

        Vec3 operator+(const Vec3& b) const;
        Vec3 operator-(const Vec3& b) const;
        Vec3 operator*(const double b) const;
        Vec3 operator/(const double b) const;

        Vec3& operator=(const Vec3& b);
        double& operator[](const int ix);

        friend std::ostream& operator<<(std::ostream& os, const Vec3& v);
        friend Vec3 operator*(double a, const Vec3& b){ return b * a;};
};

const inline Vec3 Vec3::Zero = Vec3(0,0,0);
const inline Vec3 Vec3::X = Vec3(1,0,0);
const inline Vec3 Vec3::Y = Vec3(0,1,0);
const inline Vec3 Vec3::Z = Vec3(0,0,1);


#endif
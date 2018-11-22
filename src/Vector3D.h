//
// Created by talos on 20/11/18.
//

#ifndef INC_3DWORD_POINT3D_H
#define INC_3DWORD_POINT3D_H

#include <cstdbool>
#include <iostream>
#include <math.h>

struct Vector3D {
    Vector3D() : x{0}, y{0}, z{0} {}
    Vector3D(double xv, double yv, double zv) : x{xv}, y{yv}, z{zv} {}
    ~Vector3D() = default;

    double x, y, z;

    // Operator overloaded functions
    Vector3D operator+(const Vector3D &other) const;
    Vector3D operator-(const Vector3D &other) const;
    Vector3D operator*(const double a) const;

    // Member functions
    double mag() const;
    double distance(const Vector3D &other) const;
    inline bool is_close(const Vector3D &other) const;
    inline bool is_close(const Vector3D &other, double eps) const;
    Vector3D normal() const;
    void normalize();

    friend std::ostream &operator<<(std::ostream &os, Vector3D const &point);

    // Class customization parameters
    static int print_precision;
    static double eps_distance;

  private:
    mutable double _mag = 0.0;
};

inline Vector3D Vector3D::operator+(const Vector3D &other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

inline Vector3D Vector3D::operator-(const Vector3D &other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

inline double Vector3D::distance(const Vector3D &other) const {
    auto diff = other - *this;
    return diff.mag();
}

inline bool Vector3D::is_close(const Vector3D &other) const {
    return distance(other) <= Vector3D::eps_distance;
}

inline bool Vector3D::is_close(const Vector3D &other, double eps) const {
    return distance(other) <= eps;
}

#endif // INC_3DWORD_POINT3D_H

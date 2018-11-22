#include "Vector3D.h"
#include <iomanip>

// Static class member initialization
int Vector3D::print_precision = 2;
double Vector3D::eps_distance = 0.01;

std::ostream &operator<<(std::ostream &os, Vector3D const &point) {
    // Store stream format parameters
    std::ios oldState{nullptr};
    oldState.copyfmt(os);
    os << std::fixed << std::setprecision(Vector3D::print_precision);

    auto &stream = os << "(" << point.x << "," << point.y << "," << point.z << ")";

    // Restore stream format parameters
    os.copyfmt(oldState);
    return stream;
}

double Vector3D::mag() const {
    // Do a memoization just for the fun of it
    // Function is still a constant function
    if (_mag == 0)
        _mag = sqrt(x * x + y * y + z * z);
    return _mag;
}

Vector3D Vector3D::normal() const {
    auto mag = this->mag();
    return Vector3D(x / mag, y / mag, z / mag);
}

void Vector3D::normalize() {
    auto mag = this->mag();
    x /= mag;
    y /= mag;
    z /= mag;
}

Vector3D Vector3D::operator*(const double a) const { return Vector3D(a * x, a * y, a * z); }

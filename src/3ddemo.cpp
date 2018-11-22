#include <iostream>
#include <ostream>

#include "DebugStream.h"
#include "Simulation.h"
#include "Vector3D.h"

int main() {
    debug << "Running with debug enabled.\n";

    // Set Point print precision
    Vector3D::print_precision = 2;
    Simulation::setMaxSteps(100);

    auto sim1 = Simulation{};
    sim1.setVelocity(10.0);
    sim1.setTimestep(0.2);

    sim1.setLocation(Vector3D(10, 10, 10));
    sim1.setTarget(Vector3D(-1, 20, 3));

    sim1.go();

    std::cout << sim1 << std::endl;

    return 0;
}
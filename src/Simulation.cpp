#include "Simulation.h"
#include "DebugStream.h"
#include <iomanip>

double Simulation::timestep_default = 0.1;
size_t Simulation::maxSteps = 100;
int Simulation::print_precision = 2;

std::ostream &operator<<(std::ostream &os, Simulation const &sim) {
    // Store stream format parameters
    std::ios oldState{nullptr};
    oldState.copyfmt(os);
    os << std::fixed << std::setprecision(Simulation::print_precision);

    auto &stream = os << "Simulation[t=" << sim.current_time << ", dT=" << sim.timestep
                      << ", v=" << sim.velocity << "]@" << sim.current_location;

    // Restore stream format parameters
    os.copyfmt(oldState);
    return stream;
}

const Vector3D &Simulation::getLocation() const { return current_location; }

void Simulation::setLocation(const Vector3D &location) {
    current_location = location;
    debug << "* Location now is " << location << "\n";
}

double Simulation::getVelocity() const { return velocity; }

void Simulation::setVelocity(double new_velocity) {
    if (new_velocity > 0) {
        velocity = new_velocity;
        debug << "* Velocity now is " << velocity << "\n";
    } else {
        // TODO: Refactor for better error reporting.
        // Why void?
        std::cerr << "Really? negative? '" << new_velocity << "' In what universe?.\n";
    }
}

void Simulation::setTarget(const Vector3D &new_location) {
    target_location = new_location;
    auto diff = target_location - current_location;
    velocity_vector = diff.normal();
    debug << "* Target now is " << target_location << "\n";
    debug << "* Distance is " << diff << "\n";
    debug << "* Velocity vector is " << diff << "\n";
}

bool Simulation::go() {
    debug << "* Simulation started\n";
    size_t current_step = 0;
    bool success = false;

    while (current_step <= Simulation::maxSteps) {
        // debug << "\t* Simulation step 1" << current_time << "\n";

        step();
        if (target_location.is_close(current_location, velocity_vector.mag())) {
            std::cout << "Target reached !\n";
            success = true;
            break;
        } else {
            print_sim_progress();
        }

        current_step++;
        current_time = current_time + Simulation::timestep;
    }

    if (!success) {
        std::cout << "Cant reach target in time !\n";
    }
    return success;
}

void Simulation::print_sim_progress() {
    // Store stream format parameters
    std::ios oldState{nullptr};
    oldState.copyfmt(std::cout);
    std::cout << std::fixed << std::setprecision(Simulation::print_precision);
    std::cout << "Time " << current_time << " @ " << current_location << std::endl;
    std::cout.copyfmt(oldState);
}

void Simulation::step() {
    current_location.x += velocity_vector.x * timestep * velocity;
    current_location.y += velocity_vector.y * timestep * velocity;
    current_location.z += velocity_vector.z * timestep * velocity;
    current_time = current_time + timestep * velocity;
}

double Simulation::getTimestep() const { return timestep; }

void Simulation::setTimestep(double timestep) { Simulation::timestep = timestep; }

void Simulation::setMaxSteps(size_t maxSteps) { Simulation::maxSteps = maxSteps; }

double Simulation::getCurrent_time() const { return current_time; }

const Vector3D &Simulation::getTarget_location() const { return target_location; }

size_t Simulation::getMaxSteps() { return maxSteps; }

const Vector3D &Simulation::getVelocity_vector() const { return velocity_vector; }

int Simulation::getPrint_precision() { return print_precision; }

void Simulation::setPrint_precision(int print_precision) {
    Simulation::print_precision = print_precision;
}

#ifndef INC_3DWORD_SIMULATION_H
#define INC_3DWORD_SIMULATION_H

#include "Vector3D.h"
#include <iostream>

class Simulation {
  public:
    Simulation() : timestep{Simulation::timestep_default} {}
    bool go();
    void step();

    explicit Simulation(double timestep) : timestep{timestep} {}

    friend std::ostream &operator<<(std::ostream &os, Simulation const &sim);

    const Vector3D &getLocation() const;
    void setLocation(const Vector3D &location);

    double getVelocity() const;
    void setVelocity(double velocity);

    double getTimestep() const;
    void setTimestep(double timestep);

    void setTarget(const Vector3D &targetLocation);
    const Vector3D &getTarget_location() const;
    const Vector3D &getVelocity_vector() const;

    double getCurrent_time() const;
    static int getPrint_precision();

    static void setPrint_precision(int print_precision);

    static void setMaxSteps(size_t maxSteps);

    static size_t getMaxSteps();

  private:
    void print_sim_progress();

    Vector3D current_location;
    Vector3D target_location;

    double velocity = 0.0;
    double timestep;
    double current_time = 0.0;
    Vector3D velocity_vector;

    // Static class parameters
    static double timestep_default;
    static size_t maxSteps;

    static int print_precision;
};

#endif // INC_3DWORD_SIMULATION_H

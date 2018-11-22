//
// Created by talos on 22/11/18.
//

#include "sim_commands.h"
#include <string>

// TODO: Move to a seperate file
// https://dev.krzaq.cc/post/switch-on-strings-with-c11/

typedef std::uint64_t hash_t;
namespace fnv1a_64 {

constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;

constexpr hash_t hash_compile_time(char const *str, hash_t last_value = basis) {
    return *str ? hash_compile_time(str + 1, (*str ^ last_value) * prime) : last_value;
}

hash_t hash(char const *str) {
    hash_t ret{basis};

    while (*str) {
        ret ^= *str;
        ret *= prime;
        str++;
    }

    return ret;
}

} // namespace fnv1a_64

// C++11 String literal
constexpr hash_t operator"" _hash(char const *p, size_t) { return fnv1a_64::hash_compile_time(p); }

cmdMap commands; // NOLINT

void init_commands() {
    commands["help"] = &help_cmd;
    commands["go"] = &go_cmd;
    commands["config"] = &config_cmd;
    commands["set"] = &set_cmd;
    commands["status"] = &status_cmd;
    commands["target"] = &target_cmd;
    commands["velocity"] = &velocity_cmd;
}

bool help_cmd(Simulation &, tokenList &) {
    std::cout << "HELP:" << std::endl;
    std::cout << "   check on the scripts folder :-)" << std::endl;
    return true;
}

bool go_cmd(Simulation &s, tokenList &) { return s.go(); }

bool config_cmd(Simulation &s, tokenList &) {
    std::cout << "Configuration\n";
    std::cout << "  Vector precision:\t" << Vector3D::print_precision << std::endl;
    std::cout << "  Simulation precision:\t" << s.getPrint_precision() << std::endl;
    return true;
}

bool status_cmd(Simulation &s, tokenList &) {
    std::cout << "Simulation status\n";
    std::cout << "  Time:\t\t" << s.getCurrent_time() << std::endl;
    std::cout << "  Timestep:\t" << s.getTimestep() << std::endl;
    std::cout << "  maxSteps:\t" << Simulation::getMaxSteps() << std::endl;
    std::cout << std::endl;
    std::cout << "  Velocity:\t" << s.getVelocity() << std::endl;
    std::cout << "  Velocity v:\t" << s.getVelocity_vector() << std::endl;
    std::cout << "  Location:\t" << s.getLocation() << std::endl;
    std::cout << "  Target:\t" << s.getTarget_location() << std::endl;
    return true;
}

bool set_cmd(Simulation &s, tokenList &tokens) {
    if (tokens.size() < 2) {
        std::cerr << "Error: set item value \n";
        return false;
    }
    auto parameter = tokens[1];

    switch (fnv1a_64::hash(parameter.c_str())) {
    case "target"_hash:
        return set_cmd_target(s, tokens);
        break;
    case "velocity"_hash:
        return set_cmd_velocity(s, tokens);
        break;
    case "maxsteps"_hash:
        return set_cmd_maxSteps(s, tokens);
        break;
    case "timestep"_hash:
        return set_cmd_timestep(s, tokens);
        break;
    case "precision"_hash:
        return set_cmd_precision(s, tokens);
        break;
    default:
        std::cerr << "ERROR: unknown parameter '" << parameter << "'.\n";
    }

    return false;
}

bool set_cmd_maxSteps(Simulation &s, tokenList &tokens) {
    if (tokens.size() < 3) {
        std::cerr << "Error: set maxSteps value\n";
        return false;
    }

    size_t v;
    try {
        v = std::stoul(tokens[2]);
    } catch (...) {
        std::cerr << "Error: set maxSteps invalid value\n";
        return false;
    }

    Simulation::setMaxSteps(v);
    return true;
}

bool set_cmd_precision(Simulation &s, tokenList &tokens) {
    if (tokens.size() < 3) {
        std::cerr << "Error: set precision value\n";
        return false;
    }

    int v;
    try {
        v = std::stoi(tokens[2]);
    } catch (...) {
        std::cerr << "Error: set maxSteps invalid value\n";
        return false;
    }

    Vector3D::print_precision = v;
    Simulation::setPrint_precision(v);
    return true;
}

bool set_cmd_timestep(Simulation &s, tokenList &tokens) {
    if (tokens.size() < 3) {
        std::cerr << "Error: set timestep value\n";
        return false;
    }

    double v;
    try {
        v = std::stod(tokens[2]);
    } catch (...) {
        std::cerr << "Error: set timestep invalid value\n";
        return false;
    }

    s.setTimestep(v);
    return true;
}

bool set_cmd_target(Simulation &s, tokenList &tokens) {
    if (tokens.size() < 5) {
        std::cerr << "Error: set target X Y Z\n";
        return false;
    }

    double x, y, z;
    try {
        x = std::stod(tokens[2]);
        y = std::stod(tokens[3]);
        z = std::stod(tokens[4]);
    } catch (...) {
        std::cerr << "Error: set target invalid value(s).\n";
        return false;
    }

    s.setTarget(Vector3D(x, y, z));
    return true;
}

// TODO: refactor set_cmd_target and target_cmd
bool target_cmd(Simulation &s, tokenList &tokens) {
    if (tokens.size() < 4) {
        std::cerr << "Error: target X Y Z\n";
        return false;
    }

    double x, y, z;
    try {
        x = std::stod(tokens[1]);
        y = std::stod(tokens[2]);
        z = std::stod(tokens[3]);
    } catch (...) {
        std::cerr << "Error:  target invalid value(s).\n";
        return false;
    }

    s.setTarget(Vector3D(x, y, z));
    return true;
}

bool set_cmd_velocity(Simulation &s, tokenList &tokens) {
    if (tokens.size() < 3) {
        std::cerr << "Error: set velocity value\n";
        return false;
    }

    double v;
    try {
        v = std::stod(tokens[2]);
    } catch (...) {
        std::cerr << "Error: set velocity invalid value\n";
        return false;
    }

    s.setVelocity(v);
    return true;
}

bool velocity_cmd(Simulation &s, tokenList &tokens) {
    if (tokens.size() < 2) {
        std::cerr << "Error:  velocity value\n";
        return false;
    }

    double v;
    try {
        v = std::stod(tokens[1]);
    } catch (...) {
        std::cerr << "Error: velocity invalid value\n";
        return false;
    }

    s.setVelocity(v);
    return true;
}
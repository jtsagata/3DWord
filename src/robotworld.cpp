#include "DebugStream.h"
#include "Simulation.h"
#include "Vector3D.h"
#include "repl_tools.h"
#include "sim_commands.h"

int main() {
    debug << "Running with debug enabled.\n";
    auto simulation = Simulation{};

    // Initialize the commands
    init_commands();

    std::string input;
    bool cmd_success = true;
    prompt(cmd_success);
    while (std::getline(std::cin, input)) { // quit the program with ctrl-d
        input = trim(input);
        // debug << "->" << input << "\n";
        // Ignore empty lines
        if (input.length() == 0) {
            prompt(cmd_success);
            continue;
        }

        // ignore comments
        if (input[0] == '#') {
            prompt(cmd_success);
            continue;
        }

        auto tokens = split(input);
        // Quit is a very special command
        if (tokens[0] == "quit") {
            std::cout << "BYE.\n";
            break;
        }

        auto cmd = commands.find(tokens[0]);
        if (cmd != end(commands)) {
            // execute the command
            cmd_success = (cmd->second)(simulation, tokens);
        } else {
            std::cout << "ERROR Unkown command : '" << tokens[0] << "'" << std::endl;
        }
        prompt(cmd_success);
    }

    return EXIT_SUCCESS;
}
//
// Created by talos on 22/11/18.
//

#ifndef INC_3DWORD_SIM_COMMANDS_H
#define INC_3DWORD_SIM_COMMANDS_H

#include "Simulation.h"
#include <functional>
#include <map>
#include <string>
#include <vector>

typedef std::vector<std::string> tokenList;
typedef std::map<std::string, std::function<bool(Simulation &s, tokenList tokens)>> cmdMap;

// The commands
bool help_cmd(Simulation &s, tokenList tokens);
bool go_cmd(Simulation &s, tokenList tokens);
bool config_cmd(Simulation &s, tokenList tokens);
bool set_cmd(Simulation &s, tokenList tokens);
bool status_cmd(Simulation &s, tokenList tokens);
bool target_cmd(Simulation &s, tokenList tokens);
bool velocity_cmd(Simulation &s, tokenList tokens);

// The set commands
bool set_cmd_maxSteps(Simulation &s, tokenList tokens);
bool set_cmd_precision(Simulation &s, tokenList tokens);
bool set_cmd_timestep(Simulation &s, tokenList tokens);
bool set_cmd_target(Simulation &s, tokenList tokens);
bool set_cmd_velocity(Simulation &s, tokenList tokens);

// Command map
void init_commands();
extern cmdMap commands;

#endif // INC_3DWORD_SIM_COMMANDS_H

//
// Created by talos on 22/11/18.
//

#ifndef INC_3DWORD_REPL_TOOLS_H
#define INC_3DWORD_REPL_TOOLS_H

#include <string>
#include <vector>

void prompt(bool status);

std::string trim(const std::string &source);

std::vector<std::string> split(const std::string &s, char delim = ' ');

#endif // INC_3DWORD_REPL_TOOLS_H

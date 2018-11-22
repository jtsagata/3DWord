//
// Created by talos on 22/11/18.
//

#include <iostream>
#include <sstream>
#include <unistd.h>

#include "repl_tools.h"

std::string trim(const std::string &source) {
    std::string s(source);
    s.erase(0, s.find_first_not_of(" \n\r\t"));
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    return s;
}

void prompt(bool status) {
    // Don't show the prompt if cin is not a tty
    if (isatty(STDIN_FILENO)) {
        std::cout << "$ ";
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        auto trimed = trim(item);
        elems.push_back(std::move(trimed));
    }
    return elems;
}

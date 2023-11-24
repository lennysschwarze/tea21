#include <fmt/chrono.h>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include "CLI/CLI.hpp"
#include <string>
#ifndef WORKSPACES_TEA21_EXERCISE_BMP_H
#define WORKSPACES_TEA21_EXERCISE_BMP_H

struct pixel {
    uint8_t red;
    uint8_t blue;
    uint8_t green;
    uint8_t grey(uint8_t red, uint8_t blue, uint8_t green);
};

class BMP {
    public: 
    std::vector<std::vector<pixel>> read(const std::string&  filename);
    bool write(const std::string&  filename);
};

#endif
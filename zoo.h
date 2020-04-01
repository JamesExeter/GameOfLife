/**
 * Declares a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 * Rich documentation for the api and behaviour the Zoo namespace can be found in zoo.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 953238
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the namespace.
// #include ...

/**
 * Declare the interface of the Zoo namespace for constructing lifeforms and saving and loading them from file.
 */
#include "grid.h"

namespace Zoo {
    Grid glider();
    Grid r_pentomino();
    Grid light_weight_spaceship();

    Grid load_ascii(const std::string& path);
    void save_ascii(const std::string& path, const Grid &grid);
    Grid load_binary(std::string path);
    void save_binary(std::string path, const Grid &grid);

};
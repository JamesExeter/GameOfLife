/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 953238
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
#include <vector>
#include "grid.h"

/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World {
private:
    //Only need to store the current grid and the next grid
    //All other required information is within the grid classes which can get through getters
    Grid current_grid;
    Grid next_grid;

    //Private function used to count for each item in a grid the number of alive neighbours it has
    unsigned int count_neighbours(unsigned int x, unsigned int y, bool toroidal);
public:
    //Four constructors for the world class (four?? four constructors Joss? That's insane)
    //One for an empty world, one for a square world, one with a given width and height and one with a pre-made grid
    World();
    explicit World(unsigned int size);
    World(unsigned int width, unsigned int height);
    explicit World(const Grid& initial_state);

    //Getters and setters that mirror that of the grid class but it returns the information relating to the current grid
    unsigned int get_width() const;
    unsigned int get_height() const;
    unsigned int get_total_cells() const;
    unsigned int get_alive_cells() const;
    unsigned int get_dead_cells() const;

    //Returns the current grid member
    const Grid& get_state() const;

    //Resizing of the current grid using a square size of width and height
    void resize(unsigned int new_square_size);
    void resize(unsigned int new_width, unsigned int new_height);

    //Used to perform a single step in the grid, updating the current grid to the next state
    void step(bool toroidal = false);

    //Used to perform multiple steps in the grid, updating the current grid to the result of n steps
    void advance(unsigned int steps, bool toroidal = false);
};
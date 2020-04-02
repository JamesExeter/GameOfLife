/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
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
#include <iostream>


/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD  = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
private:
    //Private variables and methods of the Grid class
    //A grid needs to store the width and height, the vector of cells it contains and the total number of cells
    //Everything else can be computed inside member functions
    unsigned int width;
    unsigned int height;
    unsigned int total_cells;
    std::vector<Cell> cell_grid;

    unsigned int get_index(unsigned int x, unsigned int y) const;

public:
    //Public variables and methods of the Grid class
    //Three constructors, one for empty grid, one for square grid and one for width and height
    Grid();
    explicit Grid(unsigned int square_size);
    Grid(unsigned int width, unsigned int height);

    //Getter methods
    unsigned int get_width() const;
    unsigned int get_height() const;
    unsigned int get_total_cells() const;
    unsigned int get_alive_cells() const;
    unsigned int get_dead_cells() const;
    Cell get(unsigned int x, unsigned int y) const;

    //Sets the value of a cell at a provided location
    void set(unsigned int x, unsigned int y, Cell value);

    //Resizing method that can be called using a square size of a given height and width
    void resize(unsigned int new_square_size);
    void resize(unsigned int new_width, unsigned int new_height);

    //Get overloaded function call method, used for getting a reference to a cell value at a specified location
    //Can be called for a non-const or const context for either read only or writing to.
    //Relies on the private get_index method and is used by get and set
    Cell& operator()(unsigned int x, unsigned int y);
    const Cell& operator()(unsigned int x, unsigned int y) const;

    //The methods used to manipulate the grid on a large scale, allowing a grid to be cropped, resized or merged with
    //other grids
    Grid crop(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) const;
    void merge(const Grid &other, unsigned int x0, unsigned int y0, bool alive_only = false);
    Grid rotate(int _rotation) const;

    //Overloaded friend << operator, used for outputting a grid to the screen using an ostream
    friend std::ostream& operator<<(std::ostream& os, const Grid &grid);
};


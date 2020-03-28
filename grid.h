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
    unsigned int width;
    unsigned int height;
    unsigned int total_cells;
    std::vector<Cell> cell_grid;

    unsigned int get_index(unsigned int x, unsigned int y) const;

public:
    //Public variables and methods of the Grid class
    Grid();
    explicit Grid(unsigned int size);
    Grid(unsigned int width, unsigned int height);
    unsigned int get_width() const;
    unsigned int get_height() const;
    unsigned int get_total_cells() const;
    unsigned int get_alive_cells() const;
    unsigned int get_dead_cells() const;

    Cell get(unsigned int x, unsigned int y) const;
    void set(unsigned int x, unsigned int y, Cell value);

    void resize(unsigned int new_square_size);
    void resize(unsigned int new_width, unsigned int new_height);

    std::vector<std::vector<Cell>> map_2D(const std::vector<Cell> &grid_1D, unsigned int w, unsigned int h) const;

    Cell& operator()(unsigned int x, unsigned int y);
    const Cell& operator()(unsigned int x, unsigned int y) const;

    Grid crop(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) const;

    // Merge
    void merge(Grid other, unsigned int x0, unsigned int y0, bool alive_only = false);

    // Rotate
    Grid rotate(int _rotation) const;

    friend std::ostream& operator<<(std::ostream& os, const Grid &grid);
};


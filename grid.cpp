/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author 953238
 * @date March, 2020
 */
#include "grid.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */
Grid::Grid() : width(0), height(0), total_cells(0), cell_grid(std::vector<Cell>()){}

/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */

//Initialise all of the cells to be dead
Grid::Grid(const unsigned int square_size) : width(square_size),
                                             height(square_size),
                                             total_cells(square_size*square_size),
                                             cell_grid(std::vector<Cell>(square_size * square_size, Cell::DEAD)){}

/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */
 //Initialise all of the cells to be dead
Grid::Grid(const unsigned int width, const unsigned int height) : width(width),
                                                                  height(height),
                                                                  total_cells(width * height),
                                                                  cell_grid(std::vector<Cell>(width*height, Cell::DEAD)){}

/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */
unsigned int Grid::get_width() const {
    return width;
}

/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */
unsigned int Grid::get_height() const {
    return height;
}

/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
unsigned int Grid::get_total_cells() const {
    return total_cells;
}

/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
unsigned int Grid::get_alive_cells() const {
    //Call std::cout on the cell vector, incrementing each time it finds an instance of Cell::ALIVE
    unsigned int alive_count = std::count( this->cell_grid.begin(), this->cell_grid.end(), Cell::ALIVE);
    return alive_count;
}

/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
unsigned int Grid::get_dead_cells() const {
    //The number of dead cells is simply the total number of cells minus the alive cells
    return total_cells - get_alive_cells();
}

/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */
void Grid::resize(const unsigned int new_square_size) {
    //Call the other resize function with the width and height the dimensions of new_square_size
    Grid::resize(new_square_size, new_square_size);
}

/**
 * Grid::resize(width, height)
 *
 * Resize the current grid to a new width and height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */

 void Grid::resize(const unsigned int new_width, unsigned int const new_height) {
     std::vector<Cell> resized;
     //For each cell in the original grid
     for (unsigned int i = 0; i < new_height; i++){
         for(unsigned  int j = 0; j < new_width; j++){
             //Ensures that we only attempt to index within the dimensions of the current grid
             if ((j < width && i < height) && width != 0 && height != 0){
                 //Index the grid at the current location
                 unsigned int idx = get_index(i, j);
                 //Add that cell to the new resized grid, since the new grid isn't initialised, we can just push back
                 //values onto it
                 resized.push_back(cell_grid.at(idx));
             } else {
                 //If either the new width or height is greater than the current, add on dead cells
                 resized.push_back(Cell::DEAD);
             }
         }
     }

     //The resized grid is now correct and complete, we can now swap it out with the current grid
     cell_grid.swap(resized);

     //Update all other member variables of the grid
     width = new_width;
     height = new_height;
     total_cells = width * height;
 }

/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */
unsigned int Grid::get_index(const unsigned int x, const unsigned int y) const {
    //Converts a 2D coordinate to a 1D coordinate, travel across the width y times then add the current x
    return x + (width * y);
}

/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell Grid::get(const unsigned int x, const unsigned int y) const {
    //Try to return the value of the cell at x, y using operator(), or throw an exception
    try{
        return operator()(x, y);
    } catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error for those coordinates " << oor.what() << std::endl;
        throw std::out_of_range("Cannot recover");
    }
}

/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
void Grid::set(const unsigned int x, const unsigned int y, const Cell value){
    //Try to update the value of a cell at /(x,y) using operator() or throw an exception for being out of bounds
    try {
        this -> operator()(x, y) = value;
    } catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error for those coordinates " << oor.what() << '\n';
        throw std::out_of_range("Cannot recover");
    }
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */
 Cell& Grid::operator()(unsigned int x, unsigned int y) {
    //Checks that the coordinates are valid
    if ((0 <= x && x < get_width()) && (0 <= y && y < get_height())){
        try {
            //Get the modifiable reference of the cell at x, y using get_index
            return cell_grid[get_index(x, y)];
        } catch (const std::out_of_range& oor) {
            //Handle the errors and prevent them for moving up the function call chain
            std::cerr << "Out of range error thrown, (x, y) is not a valid grid coordinate: " << oor.what() << std::endl;
            throw std::out_of_range("Cannot recover");
        }
    } else {
        throw std::out_of_range("Incorrect values provided");
    }
 }

/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

//Same at the operator() above but provides a non-modifiable reference
const Cell& Grid::operator()(unsigned int x, unsigned int y) const {
    if ((0 <= x && x < get_width()) && (0 <= y && y < get_height())){
        try {
            return cell_grid[get_index(x, y)];
        } catch (const std::out_of_range& oor) {
            std::cerr << "Out of range error thrown, (x, y) is not a valid grid coordinate: " << oor.what() << std::endl;
            throw std::out_of_range("Cannot recover");
        }
    } else {
        throw std::out_of_range("Incorrect values provided");
    }
}

/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(x, 1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */
 Grid Grid::crop(const unsigned int x0, const unsigned int y0, const unsigned int x1, const unsigned int y1) const {
     //Errors fairly self explanatory
     try {
         if ((x0 <= x1) && (y0 <= y1)){
             //If the window size is valid
             if ((0 <= x0 && x0 <= width) && (x0 <= x1 && x1 <= width) &&
                 (0 <= y0 && y0 <= height) && (y0 <= y1 && y1 <= height)){
                 //If the coordinates are all valid

                 //Create a new grid with the cropped dimensions
                 Grid sub_grid((x1-x0), (y1-y0));

                 //Create a buffer vector that can be swapped with
                 std::vector<Cell> cropped;

                 for (unsigned int i = y0; i < y1; i++){
                     for (unsigned int j = x0; j < x1; j++){
                         //For each value in the cropped area of the original grid, add it to the buffer vector
                         //Get the cell by using the get method which converts a 2d coordinate to a 1d index
                         cropped.push_back(this -> get(j, i));
                     }
                 }

                 //Swap the buffer with the grid of the new cropped grid
                 sub_grid.cell_grid.swap(cropped);

                 //Return the cropped grid whilst not modifying the original grid
                 return sub_grid;
             }
             throw std::out_of_range("One of more values not in range");
         }
         throw std::logic_error("Cropped grid window size is invalid");
     }
     catch(const std::out_of_range& oor) {
         std::cerr << "Out of range error thrown, at least one of (x0, y0), (x1, y1) is not a valid grid coordinate: " << oor.what() << std::endl;
         throw std::out_of_range("Cannot recover");
     }
     catch (const std::logic_error& le){
         std::cerr << "Logic error thrown, the window size is negative: " << le.what() << std::endl;
         throw std::logic_error("Cannot recover");
     }
 }

/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge reason to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */
 void Grid::merge(const Grid &other, const unsigned int x0, const unsigned int y0, const bool alive_only) {
     //Error handing fairly self explanatory
     try {
         //Iterate other the provided grid parameter
         for (unsigned int i = 0; i < other.get_height(); i++){
             for (unsigned int j = 0; j < other.get_width(); j++){
                 //If only updating when alive
                 if (alive_only){
                     //If the cell of the provided grid at the current index is alive, then we overwrite the current grid
                     //at that location with respect to where the other grid is placed on the current grid
                     if (other.get(i, j) == Cell::ALIVE){
                         this -> set(j+x0, i+y0, other.get(i, j));
                     }
                 } else {
                     //When overwriting all values
                     //Set the value of the current to that of the provided grid at the current index
                     //Need to add x0 and y0 into the indexing such that we have respect to the location the other grid
                     //is placed onto the current grid... confusing explanation I know
                     this -> set(j+x0, i+y0, other.get(i, j));
                 }
             }
         }
     } catch (const std::out_of_range& oor){
         std::cerr << "Out of range error thrown, the other grid does not fit within the bounds of the current grid: "
         << oor.what() << std::endl;
         throw std::out_of_range("Cannot recover");
     }
 }


/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param _rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 */
 Grid Grid::rotate(int _rotation) const {
     //Create a copy of the current grid that is to be rotated
     Grid to_rotate = *this;

     //Need to check for backwards rotations too,
     //Backwards basically means invert, so 90 = 270 and vice versa

     //Converts negative rotations into the range needed, inverting -90 and -270 multiples
     //Inverts 90 and 270 since a -90 rotation is a 270 and a -270 is a 90 rotation
     if (_rotation < 0){
         _rotation = abs(_rotation);
         if ((_rotation -1) % 4 == 0){
             _rotation = _rotation + 2;
         } else if ((_rotation - 3) % 4 == 0){
             _rotation = _rotation - 2;
         }
     }

     //If rotation is not a multiple of 4
     if (_rotation % 4 != 0){
         //If 90 or 270, (also -90 or -270)
         if (((_rotation - 1) % 4 == 0) || ((_rotation - 3) % 4 == 0)){
             //Rotating 90 degrees, flip the size of column and row
             to_rotate.width = this -> height;
             to_rotate.height = this -> width;
             for (unsigned int i = 0; i < this -> height; i++){
                 for (unsigned int j = 0; j < this -> width; j++){
                     to_rotate.set((this -> height - 1 - i), j,this->operator()(j, i));
                 }
             }
             // If rotating 270, simply rotate another 180 degrees
             if ((_rotation - 3) % 4 == 0){
                 std::reverse(to_rotate.cell_grid.begin(), to_rotate.cell_grid.end());
             }
         } else if ((_rotation - 2) % 4 == 0){
             //Rotating 180 degrees, simply reverse the vector
             std::reverse(to_rotate.cell_grid.begin(), to_rotate.cell_grid.end());
         }
     }

     //If rotation is a multiple of 4 or 0, return the original grid
     return to_rotate;
 }


/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */

//Oh boy this was like doing some hackerrank stuff
std::ostream& operator<<(std::ostream& os, const Grid &grid){
    //Image we have a 1 cell border around our current grid, this increases the width and height by 2
    for(unsigned int  i=0; i< grid.get_height()+2; i++) {
        for (unsigned int j = 0; j < grid.get_width() + 2; j++) {
            //If we are at the vertical border
            if ((i == 0) || i == grid.get_height() + 1) {
                //If we are at the left horizontal border, then top left + is placed
                if (j == 0) {
                    os << "+";
                } else if (j == grid.get_width() + 1) {
                    //Else if we are at the right horizontal border, the top right + is placed with a newline
                    os << "+" << std::endl;
                } else {
                    //We are at the vertical border but not a corner so place a -
                    os << "-";
                }
            //Not at the vertical border
            } else {
                //If at the left horizontal border
                if (j == 0){
                    //Place |
                    os << "|";
                //If at right horizontal border
                } else if (j == grid.get_width() + 1){
                    //Place | with new line
                    os << "|" << std::endl;
                } else {
                    //Not on the border of the grid so we can just place the cell value, outputting ' ' or  '#'
                    //given the cell value
                    if (grid.operator()(j - 1, i - 1) == Cell::ALIVE){
                        os << "#";
                    } else {
                        os << " ";
                    }
                }
            }
        }
    }

    //Return the finished stream output
    return os;
}


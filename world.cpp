/**
 * Implements a class representing a 2d grid world for simulating a cellular automaton.
 *      - Worlds can be constructed empty, from a size, or from an existing Grid with an initial state for the world.
 *      - Worlds can be resized.
 *      - Worlds can return counts of the alive and dead cells in the current Grid state.
 *      - Worlds can return their current Grid state.
 *
 *      - A World holds two equally sized Grid objects for the current state and next state.
 *          - These buffers are swapped after each update step.
 *
 *      - Stepping a world forward in time applies the rules of Conway's Game of Life.
 *          - https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *
 *      - Worlds have a private helper function used to count the number of alive cells in a 3x3 neighbours
 *        around a given cell.
 *
 *      - Updating the world state can conditionally be performed using a toroidal topology.
 *          - Moving off the left edge you appear on the right edge and vice versa.
 *          - Moving off the top edge you appear on the bottom edge and vice versa.
 *
 * @author 953238
 * @date March, 2020
 */
#include "world.h"

/**
 * World::World()
 *
 * Construct an empty world of size 0x0.
 *
 * @example
 *
 *      // Make a 0x0 empty world
 *      World world;
 *
 */
World::World() : current_grid(Grid()), next_grid(current_grid){}

/**
 * World::World(square_size)
 *
 * Construct a world with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x16 world
 *      World x(16);
 *
 *      // Also make a 16x16 world
 *      World y = World(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      World z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the world.
 */
World::World(const unsigned int square_size) : current_grid(Grid(square_size)),
                                               next_grid(current_grid){}

/**
 * World::World(width, height)
 *
 * Construct a world with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 world
 *      World world(16, 9);
 *
 * @param width
 *      The width of the world.
 * @param height
 *      The height of the world.
 */
World::World(const unsigned int width, const unsigned int height) : current_grid(Grid(width, height)),
                                                                    next_grid(current_grid){}


/**
 * World::World(initial_state)
 *
 * Construct a world using the size and values of an existing grid.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 *      // Make a world by using a grid as an initial state
 *      World world(grid);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      World bad_world = grid; // All around me are familiar faces...
 *
 * @param initial_state
 *      The state of the constructed world.
 */
World::World(const Grid& initial_state) : current_grid(initial_state),
                                          next_grid(current_grid){}

/**
 * World::get_width()
 *
 * Gets the current width of the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the width of the worlds grid to the console
 *      std::cout << world.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the width of the worlds grid to the console
 *      std::cout << read_only_world.get_width() << std::endl;
 *
 * @return
 *      The width of the world.
 */
unsigned int World::get_width() const {
    return current_grid.get_width();
}

/**
 * World::get_height()
 *
 * Gets the current height of the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the height of the worlds grid to the console
 *      std::cout << world.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the height of the worlds grid to the console
 *      std::cout << read_only_world.get_height() << std::endl;
 *
 * @return
 *      The height of the world.
 */
unsigned int World::get_height() const {
    return current_grid.get_height();
}

/**
 * World::get_total_cells()
 *
 * Gets the total number of cells in the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the total number of cells on the worlds current state grid to the console
 *      std::cout << world.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the total number of cells on the worlds current state grid to the console
 *      std::cout << read_only_world.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
 unsigned int World::get_total_cells() const {
     return current_grid.get_total_cells();
 }


/**
 * World::get_alive_cells()
 *
 * Counts how many cells in the world are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the number of alive cells in the worlds current state grid to the console
 *      std::cout << world.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the number of alive cells in the worlds current state grid to the console
 *      std::cout << read_only_world.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
unsigned int World::get_alive_cells() const {
    return current_grid.get_alive_cells();
}

/**
 * World::get_dead_cells()
 *
 * Counts how many cells in the world are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the number of dead cells in the worlds current state grid to the console
 *      std::cout << world.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the number of dead cells in the worlds current state grid to the console
 *      std::cout << read_only_world.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
 unsigned int World::get_dead_cells() const {
     return current_grid.get_dead_cells();
 }


/**
 * World::get_state()
 *
 * Return a read-only reference to the current state
 * The function should be callable from a constant context.
 * The function should not invoke a copy the current state.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the current state of the world to the console without copy
 *      std::cout << world.get_state() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the current state of the world to the console without copy
 *      std::cout << read_only_world.get_state() << std::endl;
 *
 * @return
 *      A reference to the current state.
 */

 const Grid& World::get_state() const {
     return current_grid;
 }

/**
 * World::resize(square_size)
 *
 * Resize the current state grid in to the new square width and height.
 *
 * The content of the current state grid should be preserved within the kept region.
 * The values in the next state grid do not need to be preserved, allowing an easy optimization.
 *
 * @example
 *
 *      // Make a grid
 *      World world(4, 4);
 *
 *      // Resize the world to be 8x8
 *      world.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */
 void World::resize(unsigned int new_square_size) {
     //Resize both the current and next grid
     current_grid.resize(new_square_size);
     next_grid.resize(new_square_size);
 }


/**
 * World::resize(new_width, new_height)
 *
 * Resize the current state grid in to the new width and height.
 *
 * The content of the current state grid should be preserved within the kept region.
 * The values in the next state grid do not need to be preserved, allowing an easy optimization.
 *
 * @example
 *
 *      // Make a grid
 *      World world(4, 4);
 *
 *      // Resize the world to be 2x8
 *      world.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */
 void World::resize(unsigned int new_width, unsigned int new_height) {
     //Resize both the current and next grid, could perform a swap action here to possibly save processing time but
     //this works
     current_grid.resize(new_width, new_height);
     next_grid.resize(new_width, new_height);
 }


/**
 * World::count_neighbours(x, y, toroidal)
 *
 * Private helper function to count the number of alive neighbours of a cell.
 * The function should not be visible from outside the World class.
 *
 * Neighbours are considered within the 3x3 square centred around the cell at x,y in the current state grid.
 * Ignore the centre coordinate, a cell is not its own neighbour.
 * Attempt to keep the logic as simple, expressive, and readable as possible.
 *
 * If toroidal = false then skip any neighbours that would be outside of the grid,
 * this assumes the grid is Cell::DEAD outside its bounds.
 *
 * If toroidal = true then correctly wrap out of bounds coordinates to the opposite side of the grid.
 *
 * This function is in World and not Grid because the 3x3 sized neighbourhood is specific to Conway's Game of Life,
 * while Grid is more generic to any 2D grid based cellular automaton.
 *
 * @param x
 *      The x coordinate of the centre of the neighbourhood.
 *
 * @param y
 *      The y coordinate of the centre of the neighbourhood.
 *
 * @param toroidal
 *      If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom.
 *
 * @return
 *      Returns the number of alive neighbours.
 */
 unsigned int World::count_neighbours(unsigned int x, unsigned int y, bool toroidal) {
     //Count initially 0
     unsigned int count = 0;
     //For a given cell, consider all of the cells adjacent to it
     for (int i = -1; i < 2; i++){
         for (int j = -1; j < 2; j++){
             //Do not check the cell itself
             if (!(i == 0 && j == 0)){
                 if (toroidal){
                     //If the grid wraps around...

                     //Had to add in int and unsigned int conversions to pipe down the wall warnings
                     //It makes sense to have the width and height as unsigned ints as they can't be negative
                     //Whereas new_x and new_y could be positive or negative so they have to be ints

                     //new_x and new_y are the coordinates of the neighbour being checked
                     int new_x = (int) x+j;
                     int new_y = (int) y+i;

                     //Checks if the neighbour is outside of the grid, if so, since toroidal, wrap around to the
                     //other side
                     if (new_x < 0){
                         new_x = (int) current_grid.get_width() - 1;
                     } else if ((unsigned) new_x > current_grid.get_width() - 1){
                         new_x = 0;
                     }

                     //Do same for y as was done for x
                     if (new_y < 0){
                         new_y = (int) current_grid.get_height() - 1;
                     } else if ((unsigned int) new_y > current_grid.get_height() - 1){
                         new_y = 0;
                     }

                     //If the neighbouring cell is alive, increment the count
                     if (current_grid.get(new_x, new_y) == Cell::ALIVE){
                         count += 1;
                     }
                 } else {
                     //If the grid doesn't wrap around
                     //As long as the adjacent cell if within the bounds of the grid...
                     if ((0 <= x+j) && (x+j < current_grid.get_width()) && ((0 <= y+i) && (y+i < current_grid.get_height()))){
                         //If that neighbour is alive, increment the count
                         if (current_grid.get(x+j, y+i) == Cell::ALIVE){
                             count += 1;
                         }
                     }
                 }
             }
         }
     }

     //All neighbours checked, return the count
     return count;
 }

/**
 * World::step(toroidal)
 *
 * Take one step in Conway's Game of Life.
 *
 * Reads from the current state grid and writes to the next state grid. Then swaps the grids.
 * Should be implemented by invoking World::count_neighbours(x, y, toroidal).
 * Swapping the grids should be done in O(1) constant time, and should not invoke a copy.
 * Try and boil the logic down to the fewest and most simple conditional statements.
 *
 * Rules: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *      - Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 *      - Any live cell with two or three live neighbours lives on to the next generation.
 *      - Any live cell with more than three live neighbours dies, as if by overpopulation.
 *      - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 *
 * @param toroidal
 *      Optional parameter. If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom. Defaults to false.
 */
 void World::step(bool toroidal){
     //For each cell in the current grid
     for (unsigned int i = 0; i < current_grid.get_height(); i++){
         for (unsigned int j = 0; j < current_grid.get_width(); j++){
             //For the current cell, count the number of neighbours it has, whether it is toroidal or not
             unsigned int neighbours = count_neighbours(j, i, toroidal);
             //If statement for the neighbours result
             if ((neighbours <= 1) || (neighbours > 3)){
                 //Dead if 0,1 or 3+ alive neighbours
                 next_grid.set(j, i, Cell::DEAD);
             } else if ((neighbours == 3) || ((neighbours == 2) && (current_grid.get(j, i) == Cell::ALIVE))){
                 //Alive if either 3 neighbours alive or if the cell is currently alive and has 3 neighbours
                 next_grid.set(j, i, Cell::ALIVE);
             }
         }
     }

     std::swap(next_grid, current_grid);
     next_grid = Grid(current_grid.get_width(), current_grid.get_height());
 }


/**
 * World::advance(steps, toroidal)
 *
 * Advance multiple steps in the Game of Life.
 * Should be implemented by invoking World::step(toroidal).
 *
 * @param steps
 *      The number of steps to advance the world forward.
 *
 * @param toroidal
 *      Optional parameter. If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom. Defaults to false.
 */
void World::advance(unsigned int steps, bool toroidal){
    //Perform the step method steps number of times
    for (unsigned int i = 0; i < steps; i++){
        this -> step(toroidal);
    }
}

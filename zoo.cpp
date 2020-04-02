/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 953238
 * @date March, 2020
 */
#include <fstream>
#include "zoo.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
 Grid Zoo::glider() {
     Grid g(3,3);
     g.set(0, 2, Cell::ALIVE);
     g.set(1, 2, Cell::ALIVE);
     g.set(2, 2, Cell::ALIVE);
     g.set(2, 1, Cell::ALIVE);
     g.set(1, 0, Cell::ALIVE);
     return g;
 }


/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
Grid Zoo::r_pentomino() {
    Grid r_p(3,3);
    r_p.set(1, 0, Cell::ALIVE);
    r_p.set(2, 0, Cell::ALIVE);
    r_p.set(0, 1, Cell::ALIVE);
    r_p.set(1, 1, Cell::ALIVE);
    r_p.set(1, 2, Cell::ALIVE);
    return r_p;
}

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship() {
    Grid l_w_p(5,4);
    l_w_p.set(1, 0, Cell::ALIVE);
    l_w_p.set(4, 0, Cell::ALIVE);
    l_w_p.set(0, 1, Cell::ALIVE);
    l_w_p.set(0, 2, Cell::ALIVE);
    l_w_p.set(4, 2, Cell::ALIVE);
    l_w_p.set(0, 3, Cell::ALIVE);
    l_w_p.set(1, 3, Cell::ALIVE);
    l_w_p.set(2, 3, Cell::ALIVE);
    l_w_p.set(3, 3, Cell::ALIVE);
    return l_w_p;
}

/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
Grid Zoo::load_ascii(const std::string& path) {
    try {
        std::ifstream inFile(path);
        if (inFile.is_open()) {
            int width;
            int height;

            inFile >> width >> height;
            if (width < 0 || height < 0){
                throw std::runtime_error("The width, height or both are negative which is invalid");
            }

            Grid out_grid(width, height);
            for (int i = 0; i < height; i++){
                for (int j = 0; j < width; j++){
                    char val = inFile.get();
                    if (val == '#'){
                        out_grid.set(j, i, Cell::ALIVE);
                    } else if (isspace(val)) {
                            out_grid.set(j, i, Cell::DEAD);
                    } else {
                        throw std::runtime_error("Read an element that was incorrect for the grid input");
                    }
                }

                if (inFile.peek() == '\n'){
                    throw std::runtime_error("Newline not encountered when expected, error in file format");
                } else {
                    inFile.get();
                }
            }

            inFile.close();
            return out_grid;
        } else {
            throw std::runtime_error("File with that name could not be opened");
        }
    } catch (const std::ifstream::failure& e){
        std::cerr << "Exception opening / reading file " << e.what() << std::endl;
        throw std::runtime_error("Cannot recover");
    }
}

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
 void Zoo::save_ascii(const std::string& path, const Grid &grid) {
     try {
         std::ofstream outFile(path);
         if (outFile.is_open()) {
             unsigned int width = grid.get_width();
             unsigned int height = grid.get_height();

             outFile << width << ' ' << height << '\n';

             for (unsigned int i = 0; i < height; i++){
                 for (unsigned int j = 0; j < width; j++){
                     Cell val = grid.get(j,i);
                     if (val == Cell::ALIVE){
                         outFile << '#';
                     } else if (val == Cell::DEAD){
                         outFile << ' ';
                     }
                 }
                 outFile << '\n';
             }

             outFile.close();
         } else {
             throw std::runtime_error("File with that name could not be opened");
         }
     } catch (const std::ifstream::failure& e){
         std::cerr << "Exception opening /reading file " << e.what() << std::endl;
     }
 }


/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */
Grid Zoo::load_binary(const std::string &path) {
    try {
        std::ifstream inFile(path, std::ios::in | std::ios::binary);
        if (inFile.is_open()) {
            unsigned int width;
            unsigned int height;
            inFile.read(reinterpret_cast<char *>(&width), sizeof(int));
            inFile.read(reinterpret_cast<char *>(&height), sizeof(int));

            std::vector<char> buffer(std::istreambuf_iterator<char>(inFile), {});
            std::vector<Cell> cells;

            Grid out_grid(width, height);

            for (auto const& value: buffer){
                for (unsigned int i = 0; i < 8; i++){
                    if (((value >> i) & 1) == 0){
                        cells.push_back(Cell::DEAD);
                    } else {
                        cells.push_back(Cell::ALIVE);
                    }
                }
            }

            if (cells.size() < (width * height)){
                throw std::runtime_error("Unexpected end to binary file, please check input");
            }

            for (unsigned int i = 0; i < height; i++){
                for (unsigned int j = 0; j < width; j++){
                    out_grid.set(j, i, cells.at(i*width + j));
                }
            }

            inFile.close();
            return out_grid;
        } else {
            throw std::runtime_error("File with that name could not be opened");
        }
    } catch (const std::ifstream::failure& e){
        std::cerr << "Exception opening / reading file " << e.what() << std::endl;
        throw std::runtime_error("Cannot recover");
    }
}

/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_binary(const std::string& path, const Grid &grid) {
    try {
        std::ofstream outFile(path, std::ios::out | std::ios::binary);
        if (outFile.is_open()) {
            unsigned int width = grid.get_width();
            unsigned int height = grid.get_height();

            outFile.write( reinterpret_cast<const char *>(&width), sizeof(width));
            outFile.write( reinterpret_cast<const char *>(&height), sizeof(height));

            int current_bit = 0;
            unsigned char bit_buffer = 0;

            for (unsigned int i = 0; i < height; i++){
                for (unsigned int j = 0; j < width; j++){
                    if (grid.get(j, i) == Cell::ALIVE){
                        bit_buffer |= (1<<current_bit);
                    } else {
                        bit_buffer |= (0<<current_bit);
                    }
                    current_bit++;
                    if (current_bit == 8){
                        outFile.write(reinterpret_cast<const char *>(&bit_buffer), sizeof(bit_buffer));
                        current_bit = 0;
                        bit_buffer = 0;
                    }
                }
            }

            while(current_bit){
                bit_buffer |= (0<<current_bit);
                current_bit++;
                if (current_bit == 8){
                    outFile.write(reinterpret_cast<const char *>(&bit_buffer), sizeof(bit_buffer));
                    current_bit = 0;
                    bit_buffer = 0;
                }
            }

            outFile.close();
        } else {
            throw std::runtime_error("File with that name could not be opened");
        }
    } catch (const std::ifstream::failure& e){
        std::cerr << "Exception opening /reading file " << e.what() << std::endl;
    }
}

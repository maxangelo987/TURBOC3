/* * * * * * * * * * * * * * * * * * * * * * * * *
 * File Name : path_solve.cpp
 * Author   : Tim Schumacher - twschum
 * Creation Date : 06-05-2016
 * Last Modified : Sat 07 May 2016 08:44:15 PM EDT
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include <inttypes.h>
#include <vector>
#include <iostream>

#include <cassert>

using namespace std;

class Node {
public:
    Node();
    ~Node();

    // Initialize the correct values to the node
    // return the color of the node to generate set of colors
    uint8_t init(uint32_t);

    // Each Node can be encoded in hex
    // 0x tt cc xx yy ( type | color | x | y )-
    uint32_t get_hex_encoding() const;

    // add all possible colors to the node
    // must be a blank node
    void add_colors(uint8_t colors);

    // character representation of the node
    char get_mark() const;

    void evaluate();

private:
    uint8_t type;
    vector<uint8_t> colors;
    uint8_t x;
    uint8_t y;
};

typedef vector< vector<Node> > board_grid_t;
//typedef Node** board_grid_t;

class Board {
public:
    /*
     * Board initializes from given input stream
     * First is board size N (NxN), followed by the entries
     */
    Board(istream&);
    ~Board();

    /*
     * prints current board layout
     */
    void print() const;

    void initialize();

private:
    board_grid_t board;
    uint32_t len;
    uint32_t num_colors;
};

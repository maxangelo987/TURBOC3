/* * * * * * * * * * * * * * * * * * * * * * * * *
 * File Name : Board.cpp
 * Author   : Tim Schumacher - twschum
 * Creation Date : 07-05-2016
 * Last Modified : Sat 07 May 2016 08:44:33 PM EDT
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Board.h"

#include <cstring>

#define BMASK 0x000000FF
#define GET_TYPE(HEX) ((HEX >> 24) & BMASK)
#define GET_COLOR(HEX) ((HEX >> 16) & BMASK)
#define GET_X(HEX) ((HEX >> 8) & BMASK)
#define GET_Y(HEX) (HEX & BMASK)

#define BLANK 0
#define SINK 1
#define PIPE 2

using namespace std;

// 0x tt cc xx yy ( type | color | x | y )-
uint8_t Node::init(uint32_t hexval) {

    type = GET_TYPE(hexval);
    uint8_t color = GET_COLOR(hexval);
    if (color) {
        colors.push_back(color);
    }
    x = GET_X(hexval);
    y = GET_Y(hexval);

    return color;
}

Node::Node() {}
Node::~Node() {}

uint32_t Node::get_hex_encoding() const {

    uint32_t h;

    // x and y
    h = (uint32_t)y | ((uint32_t)x << 8);

    // type, color determined by number of colors
    // (blank if more than 1, color, type == 0)
    if (colors.size() > 1) {
        assert(type != SINK);
        h &= 0x0000FFFF;
    }
    else {
        assert(colors.size());
        h |= ((uint32_t)type << 24) | ((uint32_t)colors[0] << 16);
    }

    return h;
}

char Node::get_mark() const {
    if (type == BLANK) {
        return '-';
    }
    else {
        assert(colors.size() == 1);
        return 'A' + colors[0] - 1; // colors start at 1
    }
}

void Node::add_colors(uint8_t colors) {
    assert(type != SINK);
    for (uint8_t i = 1; i <= colors; i++) {
        colors.push_back(color);
    }
}

void Node::evaluate() {
}

void Board::print() const {
    for (uint8_t i = 0; i < len; i++) {
        for (uint8_t j = 0; j < len; j++) {
            cout << " " << board[i][j].get_mark();
        }
        cout << '\n';
    }
    //cout << ' ';
    //for (uint8_t i = 0; i < (len * 2) - 1; i++) { cout << '-'; }
    cout << endl;
}

Board::~Board() {}

Board::Board(istream& input) {

    num_colors = 0;

    input >> len;

    // build the board to the right size...
    board = vector< vector<Node> >(len, vector<Node>(len));

    // for each node, read in, decypher and whatnot
    uint32_t hexval;
    uint32_t color;
    for (uint32_t i = 0; i < len*len; i++) {
        input >> hexval;

        color = board[GET_X(hexval)][GET_Y(hexval)].init(hexval);
        num_colors = (color > num_colors) ? color : num_colors;
    }
}

/*
 * Needs to assign all the possible colors to each of the Nodes
 */
void Board::initialize() {

}

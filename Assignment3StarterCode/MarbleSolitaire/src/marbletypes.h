#ifndef _MARBLE_TYPES_H_
#define _MARBLE_TYPES_H_

#include <iostream>

enum MarbleType {
    MARBLE_OCCUPIED, //Represents a space on the board grid which has a marble on it
    MARBLE_EMPTY,    //Represents an empty space on the board grid.
    MARBLE_INVALID   //Represents a spot in the board grid which is out of bounds
};

/*
 * This move struct is a simple way to represent a move from one location
 * to another location as represented by the start and end, row and column
 * values. This struct will be helpful with the isValidMove(), makeMove(),
 * and undoMove() function available in marbles.cpp.
 */
struct Move {
    Move(){
        startRow = 0;
        startCol = 0;
        endRow = 0;
        endCol = 0;
    }

    Move(int sr, int sc, int er, int ec) {
        startRow = sr;
        startCol = sc;
        endRow = er;
        endCol = ec;
    }

    int startRow;
    int startCol;
    int endRow;
    int endCol;
};

bool operator<(const MarbleType mt1, const MarbleType mt2);
std::ostream & operator<<(std::ostream & os, const Move& m);
bool operator<(const Move m1, const Move m2);


#endif //_MARBLE_TYPES_H_

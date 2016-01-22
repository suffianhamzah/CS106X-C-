#ifndef MARBLEGRAPHICS_H
#define MARBLEGRAPHICS_H

#include "marbletypes.h"
#include "map.h"
#include "gobjects.h"
#include "gwindow.h"
#include "grid.h"
#include "gevents.h"
#include <string>
using namespace std;

struct Coord {
    Coord(){
        row = 0;
        col = 0;
    }

    Coord(int r, int c) {
        row = r;
        col = c;
    }

    int row;
    int col;
};

class MarbleGraphics : private GWindow
{
public:

    MarbleGraphics();
    virtual ~MarbleGraphics();

    /*
     * Initializes board graphics with marbles placed in locations
     * indicated by board parameter
     */
    void drawBoard(Grid<MarbleType>& board);

    /*
     * Moves marble graphic according to move parameter
     *
     * Returns FALSE if move is not valid according to current
     * graphics state, otherwise returns TRUE.
     */
    bool makeMove(const Move move);

    /*
     * Removes all marbles from window
     */
    void clearBoard();

    /*
     * Processes two mouse clicks to move a marble and saves
     * the move in the provided move struct and RETURNS true.
     *
     * If the user clicks the button indicating the computer
     * should solve the puzzle, RETURNS false.
     */
    bool getNextUserMove(Move& move);

    /*
     * Makes a noise and flash to notify user of user error.
     */
    void errorNotification();

private:
    string pickRandomImage();

    GImage* boardBackground;
    Grid<GImage*> marbles;
    Grid<GOval*> spaces;
    Map<GImage*,Coord> marbleCoords;
    Map<GOval*,Coord> spaceCoords;
    GRect* solveButton;
    GLabel* solveWords;
    GRect * flash;
};

#endif // MARBLEGRAPHICS_H

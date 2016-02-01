/**
 * File: ssview.h
 * --------------
 * This file defines the interface for SSView class used in the
 * Stanford 1-2-3 spreadsheet program.
 */

#ifndef _ssview_
#define _ssview_

#include <string>
#include "gtable.h"
#include "gwindow.h"

/*********************************************************
 * NOTE: DO NOT EDIT THIS CLASS UNLESS DOING EXTENSIONS. *
 *********************************************************/

/**
 * Class constants: kNumRowsDisplayed, kNumColsDisplayed
 * Usage: int count = kNumRowsDisplayed;
 * --------------------------------------------
 * Constants that control the number of visible rows/cols
 * in the graphics window.
 */

static const int kNumRowsDisplayed = 35;
static const int kNumColsDisplayed = 20;

/**
 * Class: SSView
 * --------------
 * This class handles the display of a spreadsheet in the graphics
 * window. It exports two public member functions, one to display the
 * spreadsheet grid/labels/background, and another to display the
 * contents for a given cell. The member functions are intended to
 * be invoked by the model when cells are updated.
 */

class SSView : private GWindow {
public:

/**
 * Constructor: SSView
 * Usage: SSView view;
 * -------------------
 * The constructor initializes the graphics window, configures
 * the view object, and displays an empty spreadsheet.
 */

    SSView();

/**
 * Member function: displayEmptySpreadsheet
 * Usage: view.displayEmptySpreadsheet();
 * -------------------------------------
 * This member function draws an empty spreadsheet. It will erase any
 * previous contents by filling the background. It then redraws the
 * grid and row/col labels. All cells are drawn empty.
 */

    void displayEmptySpreadsheet();

/**
 * Member function: displayCell
 * Usage: view.displayCell(name, contents);
 * ----------------------------------------
 * This member function draws the contents for a given cell.
 * Cell name format is column letter followed by row number, e.g. "A7".
 * Columns are lettered starting from 'A'. Rows are numbered starting from 1.
 * Note that rows are not zero-based (typical users don't count from zero!)
 * An error is raised if cellname is invalid. The string is drawn
 * right-aligned within the cell. If the string is too long, it is
 * truncated to fit the cell.
 */

    void displayCell(const std::string& cellname, const std::string& txt);

private:
    GTable table;
    void labelAxes();
};

#endif

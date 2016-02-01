/**
 * File: ssview.cpp
 * -----------------
 * This file implements the ssview.h interface, which provides
 * the graphical view for the Stanford 1-2-3 program.
 *
 * Autumn 2007 Julie Zelenski (original implementation)
 * Autumn 2012 Jerry Cain
 * Autumn 2015 Ilan Goodman
 */

#include "gobjects.h"
#include "ssview.h"
#include "ssutil.h"

using namespace std;

/**
 * General implementation notes
 * ----------------------------
 * This file implements the spreadsheet graphical view for the
 * Stanford 1-2-3 program. It makes straightforward use of the extended
 * graphics library to draw the grid, labels, cell contents, and
 * so forth. The implementations of the individual member functions
 * are fairly simple, and you are feel free to change these if
 * you get inspired. For descriptions of the behavior of the
 * exported functions, please see the interface file.
 */

static const double kRowHeight = 15;
static const double kColWidth = 75;
static const double kColHeaderHeight = 5;

static const string kWindowTitle = "Stanford 1-2-3";

static const string kPlainFont = "Courier-PLAIN-12";

SSView::SSView() : GWindow((kNumColsDisplayed + 1) * kColWidth,
                           kColHeaderHeight + (kNumRowsDisplayed + 2) * kRowHeight + 1)
                 , table(kNumRowsDisplayed, kNumColsDisplayed + 1) {
    setWindowTitle(kWindowTitle);
    table.setEditable(false);
    add(&table);
    displayEmptySpreadsheet();
}

void SSView::displayEmptySpreadsheet() {
    table.clear();
    table.setFont(kPlainFont);
    table.setHorizontalAlignment(GTable::Alignment::CENTER);
    labelAxes();
}

void SSView::displayCell(const string& cellname, const string& txt) {
    location loc;
    if (!stringToLocation(cellname, loc)) {
        error("displayCell called with invalid cell name " + cellname);
    }

    table.set(loc.row, loc.col - 'A' + 1, txt);
}

/* Note: we treat the axes as cells that are editable in the GTable,
 * so to extend this be sure you have special error handling code for
 * when the user tries to update the axes (don't allow it).
 */
void SSView::labelAxes() {
    for (int row = 1; row < kNumRowsDisplayed; row++) {
        table.set(row, 0, integerToString(row));
    }
    for (int col = 1; col <= kNumColsDisplayed; col++) {
        table.set(0, col, string("") + char('A' + col - 1));
    }
}


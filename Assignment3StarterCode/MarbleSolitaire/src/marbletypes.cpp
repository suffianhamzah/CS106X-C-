#include "marbletypes.h"

/* Allows MarbleType to be put into data structures
 * which require sorting like a Map. */
bool operator<(const MarbleType mt1, const MarbleType mt2){
    return int(mt1) < int(mt2);
}

/* Makes it easy to print out Moves in a nice format. */
std::ostream & operator<<(std::ostream & os, const Move& m) {
   os << "(" << m.startRow << "," << m.startCol << ") to (" << m.endRow << "," << m.endCol;
   return os << ")";
}

/* Allows Moves to be put into data structures
 * which require sorting like a Map. */
bool operator<(const Move m1, const Move m2){
    if (m1.startRow < m2.startRow) return true;
    if (m1.startRow > m2.startRow) return false;
    if (m1.startCol < m2.startCol) return true;
    if (m1.startCol > m2.startCol) return false;
    if (m1.endRow < m2.endRow) return true;
    if (m1.endRow > m2.endRow) return false;
    if (m1.endCol < m2.endCol) return true;
    if (m1.endCol > m2.endCol) return false;
    return false;
}

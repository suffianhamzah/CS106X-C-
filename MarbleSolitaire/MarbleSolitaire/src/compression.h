#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "grid.h"
#include "marbletypes.h"

using namespace std;

/* Takes in a Marble Board and encodes it in a 32-bit unsigned
 * integer. This is done to save memory since a 7x7 Grid takes
 * up much more space than 32 bits. By encoding the boards,
 * we can store millions of boards in memory without slowing
 * down the program.
 *
 * Precondition: Board must have at most 32 valid positions.
 *
 * Returns a uint32_t variable which is an unsigned integer that
 * takes up exactly 32 bits. "unsigned" means that the integer doesn't
 * try to represent negative numbers so instead of being able to hold
 * numbers between -2^31 to 2^31 it can now hold numbers between
 * 0 to 2^32. This is a special integer type that is available from
 * the std namespace.
 */
uint32_t compressMarbleBoard(const Grid<MarbleType>& board);

#endif // COMPRESSION_H

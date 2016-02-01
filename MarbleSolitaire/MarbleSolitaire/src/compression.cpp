#include "compression.h"

uint32_t compressMarbleBoard(const Grid<MarbleType>& board){
    // Set all bits in encoding to 0
    uint32_t encoding = 0;
    int place = 0;
    for(int r = 0; r < board.numRows(); r++){
        for(int c = 0; c < board.numCols(); c++){
            if(board[r][c] == MARBLE_OCCUPIED){
                /* This line turns on the ith bit where i == place
                 * so each marble (occupied vs. empty) is encoded by 1 bit. */
                encoding |= (1 << place);
                place++;
            } else if (board[r][c] == MARBLE_EMPTY){
                place++;
            }
        }
    }
    return encoding;
}

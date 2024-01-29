#ifndef GOL_BOARD_H
#define GOL_BOARD_H

#include <stdbool.h>

/*
(0,0) -> (x, 0)
 |   \
 v    \
(0, y)  (x,y)

grid goes row by row
*/
typedef struct
{
    int rows;
    int cols;
    bool grid[0];
} board;

board * init_board(int rows, int cols, int start_cells);
board * update_board(board *b);
board * create_board_copy(board *b);
bool board_compare(board *b1, board *b2);
#endif

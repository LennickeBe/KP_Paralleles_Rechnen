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
void update_board(board *b);
void update_board_threaded(board *b);
board * create_board_copy(board *b);
#endif
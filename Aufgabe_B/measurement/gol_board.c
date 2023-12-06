#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "gol_board.h"


bool check_state(board *b, int x, int y)
{
    return b->grid[ y * b->cols + x];
}


void set_state (board *b, int x, int y, bool state)
{
    // TODO check for limits on x and y
    b->grid[ y * b->cols + x ] = state;
}



board* init_board(int rows, int cols) {
    board *b = calloc(1, 2*sizeof(int) + (rows * cols) * sizeof(bool));
    b->rows = rows;
    b->cols = cols;
    set_state(b, 2, 1, 1);
    set_state(b, 1, 2, 1);
    set_state(b, 3, 3, 1);

    printf("%d\n", check_state(b, 2, 1));


    return b;
}
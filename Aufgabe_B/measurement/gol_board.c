#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "gol_board.h"

void coords_on_board(board *b, int *x, int *y)
{
    if ( *x < 0 || *x >= b->cols)
    {
        *x = ( b->cols + *x ) % b->cols;
    }
    if ( *y < 0 || *y >= b->cols)
    {
        *y = ( b->rows + *y) % b->rows;
    }
}


bool check_state(board *b, int x, int y)
{
    coords_on_board(b, &x, &y);
    return b->grid[ y * b->cols + x];
}


void set_state (board *b, int x, int y, bool state)
{
   coords_on_board(b, &x, &y);
   b->grid[ y * b->cols + x ] = state;
}


int get_num_neighbours(board *b , int x, int y)
{

}


board* init_board(int rows, int cols) {
    board *b = calloc(1, 2*sizeof(int) + (rows * cols) * sizeof(bool));
    b->rows = rows;
    b->cols = cols;


    // Glider
    // 001
    // 101
    // 011
    set_state(b, 2, 0, 1);
    set_state(b, 0, 1, 1);
    set_state(b, 2, 1, 1);
    set_state(b, 1, 2, 1);
    set_state(b, 2, 2, 1);

    return b;
}
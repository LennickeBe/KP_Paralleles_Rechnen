#include "gol_board.h"
#include "visualize.h"


void main ()
{
    board *b;
    b = init_board(5,5);
    create_pbm(b, "test.pbm");
}
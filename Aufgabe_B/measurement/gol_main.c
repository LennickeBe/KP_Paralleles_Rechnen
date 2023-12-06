#include "gol_board.h"
#include "visualize.h"


void main ()
{
    board *b;
    b = init_board(10,10);
    create_pbm(b, "test.pbm");
}
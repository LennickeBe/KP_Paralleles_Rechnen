#include "gol_board.h"
#include "visualize.h"
#include <stdio.h>

void main ()
{
    board *b;
    char buf[12];
    b = init_board(10,10);
    create_pbm(b, "test.pbm");
    for (int i = 0; i < 10; i++)
    {
        update_board(b);
        snprintf(buf, 12, "test%d.pbm", i);
        create_pbm(b, buf);
    }
    
}
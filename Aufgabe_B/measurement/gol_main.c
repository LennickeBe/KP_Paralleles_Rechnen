#include "gol_board.h"
#include "visualize.h"
#include <stdio.h>

void main ()
{
    board *b;
    char buf[20];
    b = init_board(20,20);
    create_pbm(b, "pbms/test.pbm");
    for (int i = 0; i < 50; i++)
    {
        update_board(b);
        snprintf(buf, 20, "pbms/test%03d.pbm", i);
        create_pbm(b, buf);
    }
    
}
#include "gol_board.h"
#include "visualize.h"

#include <stdio.h>
#include <time.h>




void main ()
{
    board *b;
    char buf[20];
    struct timespec start, end;


    b = init_board(100,100, 1500);
    create_pbm(b, "pbms/test.pbm");
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < 80; i++)
    {
        update_board(b);
        snprintf(buf, 20, "pbms/test%03d.pbm", i);
        create_pbm(b, buf);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("start: %lds %ldns\nend: %lds %ldns\n", start.tv_sec, start.tv_nsec, end.tv_sec, end.tv_nsec);
}
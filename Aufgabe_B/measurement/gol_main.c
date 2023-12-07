#include "gol_board.h"
#include "visualize.h"

#include <stdio.h>
#include <time.h>




void main ()
{
    board *b, *b1, *b2;
    char buf[20];
    struct timespec start, end;


    b = init_board(1000,1000, 150000);
    b1 = create_board_copy(b);
    b2 = create_board_copy(b);
    create_pbm(b1, "pbms/test.pbm");
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < 80; i++)
    {
        update_board(b1);
        //snprintf(buf, 20, "pbms/test%03d.pbm", i);
        //create_pbm(b1, buf);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("start: %lds %ldns\nend: %lds %ldns\n", start.tv_sec, start.tv_nsec, end.tv_sec, end.tv_nsec);

    create_pbm(b1, "pbms/foo.pbm");
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < 80; i++)
    {
        update_board_threaded(b2);
        //snprintf(buf, 20, "pbms/foo%03d.pbm", i);
        //create_pbm(b2, buf);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("start: %lds %ldns\nend: %lds %ldns\n", start.tv_sec, start.tv_nsec, end.tv_sec, end.tv_nsec);
}
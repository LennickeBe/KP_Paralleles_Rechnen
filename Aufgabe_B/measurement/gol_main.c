#include "gol_board.h"
#include "visualize.h"

#include <stdio.h>
#include <time.h>


float get_time_diff_in_s(struct timespec start, struct timespec end)
{
	return ((end.tv_sec - start.tv_sec) +
		((end.tv_nsec - start.tv_nsec) / 1000000000.0));
}


void measure(size_t board_axis, int iterations)
{

	board *b, *b1;
	char buf[20];
	struct timespec start, end;

	b = init_board(200,200, 5000);//(board_axis*board_axis)/8 );
	b1 = create_board_copy(b);

	// parallel
	create_pbm(b1, "pbms/foo.pbm");
	for (int j = 0; j < 1; j++)
	{
		b1 = create_board_copy(b);
		clock_gettime(CLOCK_MONOTONIC, &start);
		for (int i = 0; i < iterations; i++)
		{
			update_board_threaded(b1);
			snprintf(buf, 20, "pbms/foo%03d.pbm", i);
			create_pbm(b1, buf);
		}
		clock_gettime(CLOCK_MONOTONIC, &end);
		printf("start: %lds %ldns\nend: %lds %ldns\n", start.tv_sec, start.tv_nsec, end.tv_sec, end.tv_nsec);
		printf("\t = %2.4fs\n", get_time_diff_in_s(start, end));
		}
	}





void main ()
{
	measure(128, 10);
}

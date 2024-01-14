#include "gol_board.h"
#include "visualize.h"

#include <stdio.h>
#include <time.h>


float get_time_diff_in_s(struct timespec start, struct timespec end)
{
	return ((end.tv_sec - start.tv_sec) +
		((end.tv_nsec - start.tv_nsec) / 1000000000.0));
}


void visualize(size_t board_axis, int iterations)
{
	board *b;
	char buf[20];

	b = init_board(board_axis, board_axis, (board_axis*board_axis)/8 );

	for (int i = 0; i < iterations; i++)
	{
		snprintf(buf, 20, "pbms/foo%03d.pbm", i);
		create_pbm(b, buf);
		update_board_threaded(b);
	}
}


void measure(size_t board_axis, int measurement_num, int iterations)
{

	board *b, *b1;
	struct timespec start, end;

	b = init_board(board_axis, board_axis,(board_axis*board_axis)/8 );
	b1 = create_board_copy(b);

	// parallel
	for (int j = 0; j < measurement_num; j++)
	{
		b1 = create_board_copy(b);
		clock_gettime(CLOCK_MONOTONIC, &start);
		for (int i = 0; i < iterations; i++)
		{
			update_board_threaded(b1);
		}
		clock_gettime(CLOCK_MONOTONIC, &end);
		//printf("start: %lds %ldns\nend: %lds %ldns\n", start.tv_sec, start.tv_nsec, end.tv_sec, end.tv_nsec);
		//printf("\t = %2.4fs\n", get_time_diff_in_s(start, end));
	}
	printf("start: %lds %ldns\nend: %lds %ldns\n", start.tv_sec, start.tv_nsec, end.tv_sec, end.tv_nsec);
	printf("\t = %2.4fs\n", get_time_diff_in_s(start, end));

}


void main ()
{
	//visualize(200, 10);
	
	//128x128
	measure(128, 1, 1);
	//512x512
	measure(512, 1, 1);
	//2048x2048
	measure(2048, 1, 1);
	//8192x8192
	measure(8192, 1, 1);
	//32768x32768
	measure(32768, 1, 1);
	
}

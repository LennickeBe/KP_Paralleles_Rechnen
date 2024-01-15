#include "gol_main.h"
#include "gol_board.h"
#include "visualize.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


float get_time_diff_in_s(struct timespec *start, struct timespec *end)
{
	return ((end->tv_sec - start->tv_sec) +
		((end->tv_nsec - start->tv_nsec) / 1000000000.0));
}

void write_times(FILE *file, int num, struct times *meas_times)
{
	int i;
	struct timespec *start, *end;
 
	// use local scope pointer to move in mem(and improve readability)
	start = meas_times->starts;
	end = meas_times->ends;

	for (i = 0; i<num; i++)
	{
		fprintf(file, "start: %lds %ldns\nend: %lds %ldns\n", start->tv_sec, start->tv_nsec, end->tv_sec, end->tv_nsec);
		fprintf(file, "\t = %2.4fs\n", get_time_diff_in_s(start, end));
		start += sizeof(struct timespec);
		end += sizeof(struct timespec);
	}
	free(meas_times->starts);
	free(meas_times->ends);
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


void measure(size_t board_axis,
		int measurement_num,
		int iterations,
		struct times *meas_times)
{

	board *b, *b1;
	struct timespec *start, *end;

	// allocate mem for the measurement times
	meas_times->starts = malloc(measurement_num * sizeof(struct timespec));
	meas_times->ends = malloc(measurement_num * sizeof(struct timespec));
	// use local scope pointer to move in mem(and improve readability)
	start = meas_times->starts;
	end = meas_times->ends;

	// start board with 20%~ of the cells alive
	b = init_board(board_axis, board_axis,(board_axis*board_axis)/8 );

	// play the game with the same board multiple times
	for (int j = 0; j < measurement_num; j++)
	{
		// reset board
		b1 = create_board_copy(b);
		clock_gettime(CLOCK_MONOTONIC, start);
		// loop over game states
		for (int i = 0; i < iterations; i++)
		{
			update_board_threaded(b1);
		}
		clock_gettime(CLOCK_MONOTONIC, end);

		// move pointer in timespec areas
		start += sizeof(struct timespec);
		end += sizeof(struct timespec);
	}
}


void main ()
{
	struct times times[5];
	FILE *file;

	//visualize(200, 10);
	
	//128x128
	measure(128, 1, 1, &times[0]);
	//512x512
	measure(512, 1, 1, &times[1]);
	//2048x2048
	measure(2048, 1, 1, &times[2]);
	//8192x8192
	measure(8192, 1, 1, &times[3]);
	//32768x32768
	measure(32768, 1, 1, &times[4]);	
	
	// write results
	file = fopen("times128.csv", "w");
	write_times(file,1,  &times[0]);
	fclose(file);
	file = fopen("times512.csv", "w");
	write_times(file,1,  &times[1]);
	fclose(file);
	file = fopen("times2048.csv", "w");
	write_times(file,1,  &times[2]);
	fclose(file);
	file = fopen("times8192.csv", "w");
	write_times(file,1,  &times[3]);
	fclose(file);
	file = fopen("times32769.csv", "w");
	write_times(file,1,  &times[4]);
	fclose(file);
}

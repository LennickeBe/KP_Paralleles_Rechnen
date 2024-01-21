#include "gol_main.h"
#include "gol_board.h"
#include "visualize.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


float get_time_diff_in_s(struct timespec *start, struct timespec *end)
{
	return ((end->tv_sec - start->tv_sec) +
		((end->tv_nsec - start->tv_nsec) / 1000000000.0));
}

void write_times(FILE *file, int num, struct times *meas_times)
{
	int i;

	// header
	fprintf(file, "time\n");

	// set pointer to start of timespec array
	meas_times->start = *meas_times->starts;
	meas_times->end = *meas_times->ends;
 
	for (i = 0; i<num; i++)
	{
		// fprintf(file, "start: %lds %ldns\nend: %lds %ldns\n", meas_times->start->tv_sec, meas_times->start->tv_nsec, meas_times->end->tv_sec, meas_times->end->tv_nsec);
		// fprintf(file, "\t = %2.4fs\n", get_time_diff_in_s(meas_times->start, meas_times->end));
		fprintf(file, "%2.6fs\n", get_time_diff_in_s(meas_times->start, meas_times->end));
		meas_times->start++;
		meas_times->end++;
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

	// allocate mem for the measurement times
	meas_times->starts = malloc(measurement_num * sizeof(struct timespec));
	meas_times->ends = malloc(measurement_num * sizeof(struct timespec));
	// use local scope pointer to move in mem(and improve readability)
	meas_times->start = *meas_times->starts;
	meas_times->end = *meas_times->ends;

	// start board with 20%~ of the cells alive
	b = init_board(board_axis, board_axis,(board_axis*board_axis)/8 );

	// play the game with the same board multiple times
	for (int j = 0; j < measurement_num; j++)
	{
		// reset board
		b1 = create_board_copy(b);
		clock_gettime(CLOCK_MONOTONIC, meas_times->start);
		// loop over game states
		for (int i = 0; i < iterations; i++)
		{
			update_board_threaded(b1);
		}
		clock_gettime(CLOCK_MONOTONIC, meas_times->end);

		// move pointer in timespec areas
		meas_times->start++;
		meas_times->end++;
	}
	// reset pointer to start of timespec array
	meas_times->start = *meas_times->starts;
	meas_times->end = *meas_times->ends;

}



char* concat(char *s1, char *s2)
{
    char *result;
    // +1 for '\0' at the end
    result = malloc(strlen(s1) + strlen(s2) + 1);
    // add first string
    strcpy(result, s1);
    // append second string
    strcat(result, s2);
    return result;
}

void main ()
{
	struct times meas_times[5];
	FILE *file;
	int iterations = 20;

	char *path;
       	path = concat(concat("../evaluation/data/", COMPILER_STR),
		      concat("/", THREADS_STR));


	//visualize(200, 10);
	
	//128x128
	measure(128, iterations, 1, &meas_times[0]);
	//512x512
	measure(512, iterations, 1, &meas_times[1]);
	//2048x2048
	measure(2048, iterations, 1, &meas_times[2]);
	//8192x8192
	measure(8192, iterations, 1, &meas_times[3]);
	//32768x32768
	measure(32768, iterations, 1, &meas_times[4]);	

	// write results
	file = fopen(concat(path,
			    concat("/","times128.csv")), "w");
	write_times(file, iterations,  &meas_times[0]);
	fclose(file);
	file = fopen(concat(path,
			    concat("/","times512.csv")), "w");
	write_times(file, iterations,  &meas_times[1]);
	fclose(file);
	file = fopen(concat(path,
			    concat("/","times2048.csv")), "w");
	write_times(file, iterations,  &meas_times[2]);
	fclose(file);
	file = fopen(concat(path,
			    concat("/","times8192.csv")), "w");
	write_times(file, iterations,  &meas_times[3]);
	fclose(file);
	file = fopen(concat(path,
			    concat("/","times32768.csv")), "w");
	write_times(file, iterations,  &meas_times[4]);
	fclose(file);
}

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

void write_times(FILE *file, int num, struct times *meas_times, int iterations)
{
	int i;

	// header
	fprintf(file, "time[s]\n");

	// set pointer to start of timespec array
	meas_times->start = *meas_times->starts;
	meas_times->end = *meas_times->ends;
 
	for (i = 0; i<num; i++)
	{
		fprintf(file, "%2.6f\n",
			get_time_diff_in_s(meas_times->start, meas_times->end)/iterations);
		meas_times->start++;
		meas_times->end++;
	}
	free(meas_times->starts);
	free(meas_times->ends);
}



void visualize(size_t board_axis, int iterations)
{
	board *b, *b2, *tmp;
	char buf[20];

	b = init_board(board_axis, board_axis,0);
	b2 = init_board(board_axis, board_axis, 0);
	for (int i = 0; i < iterations; i++)
	{
		snprintf(buf, 20, "pbms/foo%03d.pbm", i);
		create_pbm(b, buf);
		update_board(b, b2);
		tmp = b;
		b = b2;
		b2 = tmp;
	}
}


void measure(size_t board_axis,
		int measurement_num,
		int iterations,
		struct times *meas_times)
{

	board *b, *b1, *buf, *tmp;

	// allocate mem for the measurement times
	meas_times->starts = malloc(measurement_num * sizeof(struct timespec));
	meas_times->ends = malloc(measurement_num * sizeof(struct timespec));
	// use local scope pointer to move in mem(and improve readability)
	meas_times->start = *meas_times->starts;
	meas_times->end = *meas_times->ends;

	// start board with 20%~ of the cells alive
	b = init_board(board_axis, board_axis,(board_axis*board_axis)/8 );
	buf = init_board(board_axis, board_axis,(board_axis*board_axis)/8 );

	// play the game with the same board multiple times
	for (int j = 0; j < measurement_num; j++)
	{
		// reset board
		b1 = create_board_copy(b);
		clock_gettime(CLOCK_MONOTONIC, meas_times->start);
		// loop over game states
		for (int i = 0; i < iterations; i++)
		{
			update_board(b1, buf);
			tmp = buf;
			buf = b1;
			b1 = tmp;
		}
		clock_gettime(CLOCK_MONOTONIC, meas_times->end);
		free(b1);
		// move pointer in timespec areas
		meas_times->start++;
		meas_times->end++;
	}
	// reset pointer to start of timespec array
	meas_times->start = *meas_times->starts;
	meas_times->end = *meas_times->ends;

	free(b);
	free(buf);

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

int main (int argc, char* argv[])
{
	//visualize(10, 200);
	//return 0;

	// no cmd arg
	if (argc==1)
	{
		struct times meas_times[5];
		FILE *file;
		int meas_num = 20;
		int iterations[5] = {100,50,20,1,1};

		char *path;
		path = concat(concat("../evaluation/data/", COMPILER_STR),
			      concat("/", THREADS_STR));


		//visualize(200, 10);
		//32768x32768
		measure(32768, meas_num, iterations[4], &meas_times[4]);	
		//8192x8192
		measure(8192, meas_num, iterations[3], &meas_times[3]);
		//2048x2048
		measure(2048, meas_num, iterations[2], &meas_times[2]);
		//512x512
		measure(512, meas_num, iterations[1], &meas_times[1]);
		//128x128
		measure(128, meas_num, iterations[0], &meas_times[0]);

		// write results
		file = fopen(concat(path,
				    concat("/","times128.csv")), "w");
		write_times(file, meas_num,  &meas_times[0], iterations[0]);
		fclose(file);
		file = fopen(concat(path,
				    concat("/","times512.csv")), "w");
		write_times(file, meas_num,  &meas_times[1], iterations[1]);
		fclose(file);
		file = fopen(concat(path,
				    concat("/","times2048.csv")), "w");
		write_times(file, meas_num,  &meas_times[2], iterations[2]);
		fclose(file);
		file = fopen(concat(path,
				    concat("/","times8192.csv")), "w");
		write_times(file, meas_num,  &meas_times[3], iterations[3]);
		fclose(file);
		file = fopen(concat(path,
				    concat("/","times32768.csv")), "w");
		write_times(file, meas_num,  &meas_times[4], iterations[4]);
		fclose(file);
		return 0;
	}
	// with cmd line arg
	// this is for the OMP_SCHEDULE measurement
	else
	{
		if ((strcmp(COMPILER_STR, "icc")!=0 ||
					(strcmp(THREADS_STR, "32")!=0)))
		{
			perror("Compiler needs to be icc and with 32 threads.\n");
			return 1;
		}

		struct times meas_times;
		FILE *file;
		int meas_num = 20, iterations=1000;

		char *path, *filename;
		path = concat(concat("../evaluation/data/", COMPILER_STR),
			      concat("/", THREADS_STR));
		filename = concat("/",
				concat(argv[1], ".csv"));
		
		measure(128, meas_num, iterations, &meas_times);
		
		file = fopen(concat(path,
				    filename), "w");
		write_times(file, meas_num,  &meas_times, iterations);
		fclose(file);
		
		return 0;

	}
}

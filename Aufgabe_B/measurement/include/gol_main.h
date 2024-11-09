#ifndef GOL_MAIN_H
#define GOL_MAIN_H

#include <stdio.h>
#include <time.h>

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

#define THREADS_STR STRINGIFY(THREADS)
#define COMPILER_STR STRINGIFY(COMPILER)

struct times {
	struct timespec (*starts)[];
	struct timespec (*ends)[];
	struct timespec *start;
	struct timespec *end;
};

/*
 *  returns time difference between two timespecs in s
 */
float get_time_diff_in_s(struct timespec *start, struct timespec *end);

/*
 * writes the time differences resulting from 'times' to the given file
 */
void write_times(FILE *file, int num, struct times *meas_times, int iterations);

/*
 * saves a pbm image of the board for each iteration
 */
void visualize(size_t board_axis, int iterations);

/*
 * runs a measurement with given board size, measurement iterations, iterations per measurement
 */
void measure(size_t board_axis,
		int measurement_num,
		int iterations,
		struct times *meas_times);

/*
 * returns a new string containing the concatenation of the given ones
 */
char* concat(char *s1, char *s2);

#endif

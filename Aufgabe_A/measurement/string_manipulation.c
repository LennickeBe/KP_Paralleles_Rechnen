#include "string_manipulation.h"
#include "string_manipulation_par.h"
#include "string_manipulation_seq.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
 * returns the difference between two timespec objects in ns
 */
int time_diff_in_ns(struct timespec *start, struct timespec *end)
{
	// seconds times 10^9 for nanoseconds
	return (1000000000 * (end->tv_sec - start->tv_sec) +
		(end->tv_nsec - start->tv_nsec));
}


void write_times(FILE *file, struct times *meas_times, int iterations)
{
	int i, j;
	// header for csv
	fprintf(file,
		"count_par,count_seq,upper_par,upper_seq,lower_par,lower_seq\n");

	// set pointers to move on array	
	meas_times->start = *meas_times->starts;
	meas_times->end = *meas_times->ends;

	for (i = 0; i < iterations; i++)
	{
		for (j = 0; j < 5; j++)
		{

			fprintf(file, "%d,", time_diff_in_ns(meas_times->start, meas_times->end));
			meas_times->start++;
			meas_times->end++;
		}

		fprintf(file, "%d\n", time_diff_in_ns(meas_times->start, meas_times->end));
		meas_times->start++;
		meas_times->end++;
	}
	free(meas_times->starts);
	free(meas_times->ends);
}


/*
 * returns a random int within the given range
 * utilizes the rand() method from math.h
 */
int random_int(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}


/*
 * fill a given string with random characters between 32 and 126
 * (in ascii)
 * the memory the pointer is pointing at must be allocated
 * and the size must match that space
 * returns 0 on success and -1 if the size is 0
 */
int generateString(char *str, size_t size)
{
    if (size) 
    {
        for (size_t n = 0; n < size-1; n++)
	{
		str[n] = (char) random_int(32, 126);
        }
        str[size-1] = '\0';
    }
    else
    {
	    return -1;
    }
    return 0;
}

/*
 * allocate memory for a string of size "size"
 * and fill it with a random generated string
 * returns the string
 */
char* rand_string_alloc(size_t size)
{
     char *s = malloc(size);
     if (s) {
         generateString(s, size);
     }
     return s;
}

/*
 * this function takes a string (with length len_string)
 * and measures how long it takes to run the functions
 *  toUpperPar, toUpperSeq, toLowerPar, toLowerSeq
 *  countCharPar, countCharSeq
 * and writes the times in ns in the given file in csv format
 * returns 0 on success and 1 if a parallel and sequential
 * result does not add up
 */
int measure(struct times *meas_times, char *string, int len_string)
{
	int par_count, seq_count;
	
	// string gets changed so we work with duplicates to be able to reset
	char *seq_string, *par_string;
	seq_string = malloc(len_string * sizeof(char));
	par_string = malloc(len_string * sizeof(char));
	strncpy(seq_string, string, len_string);
	strncpy(par_string, string, len_string);

	// start with count as no reset necessary after
// count
	clock_gettime(CLOCK_MONOTONIC, meas_times->start);	
	par_count = countCharPar(par_string, len_string);
	clock_gettime(CLOCK_MONOTONIC, meas_times->end);
	meas_times->start++;
	meas_times->end++;


	clock_gettime(CLOCK_MONOTONIC, meas_times->start);	
	seq_count = countCharSeq(seq_string, len_string);
	clock_gettime(CLOCK_MONOTONIC, meas_times->end);
	meas_times->start++;
	meas_times->end++;


	if (par_count != seq_count)
	{
		fprintf(stderr, "Counting does not match up.\n");
		return 1;
	}


// uppercase
	clock_gettime(CLOCK_MONOTONIC, meas_times->start);	
	toUppercasePar(par_string, len_string);
	clock_gettime(CLOCK_MONOTONIC, meas_times->end);
	meas_times->start++;
	meas_times->end++;



	clock_gettime(CLOCK_MONOTONIC, meas_times->start);	
	toUppercaseSeq(seq_string, len_string);
	clock_gettime(CLOCK_MONOTONIC, meas_times->end);
	meas_times->start++;
	meas_times->end++;



	if (strcmp(par_string, seq_string))
	{
		fprintf(stderr, "toUppercase does not match up.\n");
		return 1;
	}

// reset
	strncpy(seq_string, string, len_string);
	strncpy(par_string, string, len_string);


// lowercase
	clock_gettime(CLOCK_MONOTONIC, meas_times->start);	
	toLowercasePar(par_string, len_string);
	clock_gettime(CLOCK_MONOTONIC, meas_times->end);
	meas_times->start++;
	meas_times->end++;



	clock_gettime(CLOCK_MONOTONIC, meas_times->start);	
	toLowercaseSeq(seq_string, len_string);
	clock_gettime(CLOCK_MONOTONIC, meas_times->end);
	meas_times->start++;
	meas_times->end++;


	if (strcmp(par_string, seq_string))
	{
		fprintf(stderr, "toLowercase does not match up.\n");
		return 1;
	}
	
	free(par_string);
	free(seq_string);
	return 0;
}
	

/*
 * this functions calls the measure function "iterations" times
 * with a newly generated string of the lengt
 * it also writes the header for the csv file
 * returns 0 on success and 1 if measure returns 1
 */
int measurement(struct times *meas_times, int iterations, int len_string)
{
	char *string;
	int i;
	struct timespec *start, *end;
	//struct timespec starts[2*3*iterations], ends[2*3*iterations];
	string = rand_string_alloc(len_string);
	
	// each measurement for seq+par, for count,up,low
	// 2 * 3 * iterations timespecs
	meas_times->starts = malloc(2 * 3 * iterations * sizeof(struct timespec));
	meas_times->ends = malloc(2 * 3 * iterations * sizeof(struct timespec));
	// pointer to work on those arrays
	meas_times->start = *meas_times->starts;
	meas_times->end = *meas_times->ends;

	for(i = 0; i < iterations; i++)
	{
		if (measure(meas_times, string, len_string))
		{
			return 1;
		}
	}

	// reset worker arrays
	meas_times->start = *meas_times->starts;
	meas_times->end = *meas_times->ends;

	free(string);
	return 0;
}


int main()
{
	int len_string, iterations=100;
	struct times meas_times[4];
	FILE *file;



	init_register();

	// 10000
	file = fopen("../evaluation/data/string_times_10000.csv", "w");
	if (measurement(&meas_times[0], iterations, 1000))
	{
		return 1;
	}
	write_times(file, &meas_times[0], iterations);
	fclose(file);

	return 0;
	
	// 100000
	file = fopen("../evaluation/data/string_times_100000.csv", "w");
	if (measurement(&meas_times[1], 100, 100000))
	{
		return 1;
	}
	fclose(file);

	// 1000000
	file = fopen("../evaluation/data/string_times_1000000.csv", "w");
	if (measurement(&meas_times[2], 100, 1000000))
	{
		return 1;
	}		
	fclose(file);

	// 100000000
	file = fopen("../evaluation/data/string_times_100000000.csv", "w");
	if (measurement(&meas_times[3], 100, 100000000))
	{
		return 1;
	}
	fclose(file);

	return 0;
}

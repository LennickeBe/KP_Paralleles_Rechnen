#include "string_manipulation_par.h"
#include "string_manipulation_seq.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int time_diff_in_ns(struct timespec start, struct timespec end)
{
	return (1000000000 * (end.tv_sec - start.tv_sec) +
		(end.tv_nsec - start.tv_nsec));
}


/*
 * returns a random int within the given range
 * utilizes the rand() method from math.h
 */
int random_int(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}


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

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
	printf("\n");
    }
    puts("");
}

int measure(FILE *file, char *string, int len_string)
{
	int par_count, seq_count;
	struct timespec start, end;
	
	// string gets changed so we work with duplicates to be able to reset
	char *seq_string, *par_string;
	seq_string = malloc(len_string * sizeof(char));
	par_string = malloc(len_string * sizeof(char));
	strncpy(seq_string, string, len_string);
	strncpy(par_string, string, len_string);

	// start with count as no reset necessary after
// count
	clock_gettime(CLOCK_MONOTONIC, &start);	
	par_count = countCharPar(par_string, len_string, 'c');
	clock_gettime(CLOCK_MONOTONIC, &end);
	fprintf(file, "%d,", time_diff_in_ns(start, end));	
	clock_gettime(CLOCK_MONOTONIC, &start);	
	seq_count = countCharSeq(seq_string, len_string, 'c');
	clock_gettime(CLOCK_MONOTONIC, &end);
	fprintf(file, "%d,", time_diff_in_ns(start, end));	
	if (par_count != seq_count)
	{
		fprintf(stderr, "Counting does not match up.\n");
		return 1;
	}

// uppercase
	clock_gettime(CLOCK_MONOTONIC, &start);	
	toUppercasePar(par_string, len_string);
	clock_gettime(CLOCK_MONOTONIC, &end);
	fprintf(file, "%d,", time_diff_in_ns(start, end));	

	clock_gettime(CLOCK_MONOTONIC, &start);	
	toUppercaseSeq(seq_string, len_string);
	clock_gettime(CLOCK_MONOTONIC, &end);
	fprintf(file, "%d,", time_diff_in_ns(start, end));	
	if (strcmp(par_string, seq_string))
	{
		fprintf(stderr, "toUppercase does not match up.\n");
		return 1;
	}

// reset
	strncpy(seq_string, string, len_string);
	strncpy(par_string, string, len_string);

// lowercase
	clock_gettime(CLOCK_MONOTONIC, &start);	
	toLowercasePar(par_string, len_string);
	clock_gettime(CLOCK_MONOTONIC, &end);
	fprintf(file, "%d,", time_diff_in_ns(start, end));	

	clock_gettime(CLOCK_MONOTONIC, &start);	
	toLowercaseSeq(seq_string, len_string);
	clock_gettime(CLOCK_MONOTONIC, &end);
	fprintf(file, "%d\n", time_diff_in_ns(start, end));	
	if (strcmp(par_string, seq_string))
	{
		fprintf(stderr, "toLowercase does not match up.\n");
		return 1;
	}
	
	free(par_string);
	free(seq_string);
	return 0;
}
	
int measurement(FILE *file, int iterations, int len_string)
{
	char *string;
	int i;
	string = rand_string_alloc(len_string);
	fprintf(file,
		"count_par,count_seq,upper_par,upper_seq,lower_par,lower_seq\n");
	for(i = 0; i < iterations; i++)
	{

		if (measure(file, string, len_string))
		{
			return 1;
		}
	}
	free(string);
	return 0;
}


int main()
{
	char *test_word;
	int len_string; 	
	FILE *file;

	init_register();

	// 10000
	file = fopen("string_times_10000.csv", "w");
	if (measurement(file, 100, 10000))
	{
		return 1;
	}
	fclose(file);
	
	// 100000
	file = fopen("string_times_100000.csv", "w");
	if (measurement(file, 100, 100000))
	{
		return 1;
	}
	fclose(file);

	// 1000000
	file = fopen("string_times_1000000.csv", "w");
	if (measurement(file, 100, 1000000))
	{
		return 1;
	}		
	fclose(file);

	// 100000000
	file = fopen("string_times_100000000.csv", "w");
	if (measurement(file, 100, 100000000))
	{
		return 1;
	}
	fclose(file);

	return 0;

	// 1000:
	len_string = 10;
	test_word = rand_string_alloc(len_string);
	measure(file, test_word, len_string);
	free(test_word);	
	

	len_string = 32;
	test_word = rand_string_alloc(len_string);
	measure(file, test_word, len_string);
	free(test_word);
	
	len_string = 33;
	test_word = rand_string_alloc(len_string);
	measure(file, test_word, len_string);
	free(test_word);

	return 0;
}

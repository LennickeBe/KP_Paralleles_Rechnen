#include "string_manipulation_par.h"
#include "string_manipulation_seq.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

int measure(char *string, int len_string)
{
	// string gets changed so we work with duplicates to be able to reset
	char *seq_string, *par_string;
	seq_string = malloc(len_string * sizeof(char));
	par_string = malloc(len_string * sizeof(char));
	strncpy(seq_string, string, len_string);
	strncpy(par_string, string, len_string);

	// start with count as no reset necessary after
	int count;
	count = countCharPar(par_string, len_string, 'c');
	printf("count_par: %d\n", count);
	count = countCharSeq(seq_string, len_string, 'c');
	printf("count_seq: %d\n\n", count);


	printf("%s\n", string);

	// uppercase
	toUppercasePar(par_string, len_string);
	printf("upper_par:\n%s\n", par_string);
	toUppercaseSeq(seq_string, len_string);
	printf("upper_seq:\n%s\n\n", seq_string);

	// reset
	strncpy(seq_string, string, len_string);
	strncpy(par_string, string, len_string);

	// lowercase
	toLowercasePar(par_string, len_string);
	printf("lower_par:\n%s\n", par_string);
	toLowercaseSeq(seq_string, len_string);
	printf("lower_seq:\n%s\n\n", seq_string);

	free(par_string);
	free(seq_string);
	return 0;
}
	
int measurement(FILE *file, int iterations, int len_string)
{
	char *string;
	string = rand_string_alloc(len_string);
	fprintf(file,
		"count_par,count_seq,upper_par,upper_seq,lower_par,lower_seq\n");
	
}


int main()
{
	char *test_word;
	int len_string; 	
		
	init_register();
	
	// 1000:
	len_string = 10;
	test_word = rand_string_alloc(len_string);
	measure(test_word, len_string);
	free(test_word);	

	len_string = 32;
	test_word = rand_string_alloc(len_string);
	measure(test_word, len_string);
	free(test_word);
	
	len_string = 33;
	test_word = rand_string_alloc(len_string);
	measure(test_word, len_string);
	free(test_word);

	return 0;
}

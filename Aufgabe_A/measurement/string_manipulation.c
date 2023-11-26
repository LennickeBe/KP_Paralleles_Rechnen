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


int main()
{
	char *test_word, *result_word;
	int count; 	
	// 1000:
	test_word = rand_string_alloc(33);
	// register with chars '<' than a
	//lower_low_limit = _mm256_set1_epi8('`');
	// register with chars '>' than z
	//upper_low_limit = _mm256_set1_epi8('{');
	// register with chars '<' than A
	//lower_up_limit = _mm256_set1_epi8('@');
	// register with chars '>' than Z
	//upper_up_limit = _mm256_set1_epi8('[');
	// register with the 8-bit values '32'
	//	register_of_32 = _mm256_set1_epi8(' ');

	init_registers();	

	printf("test word before:\n%s\n", test_word);
	toUppercasePar(test_word, strlen(test_word));
	printf("test word after:\n%s\n", test_word);
	toLowercasePar(test_word, strlen(test_word));
	printf("test word after:\n%s\n", test_word);

	char *count_word; 
	count_word = rand_string_alloc(12);
	count = countCharPar(count_word, 12, 'N');
	printf("count word %s\n", count_word);
	printf("has %d\n", count);
	


	
	free(test_word);
	free(result_word);
	free(count_word);
	return 0;
}

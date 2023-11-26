#include <immintrin.h>  // intel intrinsics 
#include <stdio.h>	// io functions TODO maybe remove after testing
#include <string.h>	// TODO check if necessary before turn in
#include <stdlib.h>	// string generation (rand_r)
#include <math.h>	// for "to the power of"

#include "string_manipulation_par.h"

/*
 * Turn string in register "string" to uppercase
 * returns 1 if there has been an error, 0 if there has been no error
 */
int regToUppercase(__m256i *string)
{

	__m256i is_lower_char = _mm256_and_si256(
			_mm256_cmpgt_epi8(*string, lower_low_limit),
			_mm256_cmpgt_epi8(upper_low_limit, *string));

	*string = _mm256_sub_epi8(*string,
			_mm256_and_si256(register_of_32, is_lower_char));
	return 0;
}


/*
 * Turn string "string" (with length len_string) to uppercase
 * returns 1 if there has been an error, 0 if there has been no error
 */
int toUppercasePar(char *string, int len_string)
{
	int i, filler_size;
	char *filler_string;
	__m256i xmm;

	for ( i=0; i<=len_string-32; i+=32)
	{
		xmm = _mm256_load_si256((__m256i*) string);
		regToUppercase(&xmm);
		_mm256_store_si256((__m256i*) string, xmm);
		string+=32;
	}

	// to avoid naughty memory access last chars treated different
	filler_size = len_string % 32;
	if (filler_size != 0)
	{
		filler_string = (char*) malloc(32*sizeof(char));
		// remaining chars into allocated 32 bytes memory
		strncpy(filler_string, string, filler_size);
		xmm = _mm256_loadu_si256((__m256i*) filler_string);
		regToUppercase(&xmm);
		_mm256_storeu_si256((__m256i*) filler_string, xmm);	
		// load the relevant chars back into original string
		strncpy(string, filler_string, filler_size);
		free(filler_string);
	}
	return 0;
}


/*
 * Turn string in register "string" to lowercase
 * returns 1 if there has been an error, 0 if there has been no error
 */
int regToLowercase(__m256i *string)
{
	__m256i is_lower_char = _mm256_and_si256(
			_mm256_cmpgt_epi8(*string, lower_up_limit),
			_mm256_cmpgt_epi8(upper_up_limit, *string));

	*string = _mm256_add_epi8(*string,
			_mm256_and_si256(register_of_32, is_lower_char));
	return 0;
}


/*
 * Turn string "string" (with length len_string) to lowercase
 * returns 1 if there has been an error, 0 if there has been no error
 */
int toLowercasePar(char *string, int len_string)
{
	int i, filler_size;
	char *filler_string;
	__m256i xmm;

	for ( i=0; i<=len_string-32; i+=32)
	{
		xmm = _mm256_load_si256((__m256i*) string);
		regToLowercase(&xmm);
		_mm256_store_si256((__m256i*) string, xmm);
		string+=32;
	}

	// to avoid naughty memory access last chars treated different
	filler_size = len_string % 32;
	if (filler_size != 0)
	{
		filler_string = (char*) malloc(32*sizeof(char));
		// remaining chars into allocated 32 bytes memory
		strncpy(filler_string, string, filler_size);
		xmm = _mm256_loadu_si256((__m256i*) filler_string);
		regToLowercase(&xmm);
		_mm256_storeu_si256((__m256i*) filler_string, xmm);	
		// load the relevant chars back into original string
		strncpy(string, filler_string, filler_size);
		free(filler_string);
	}
	return 0;
}


/*
 * https://web.archive.org/web/20151229003112/http://blogs.msdn.com/b/jeuge/archive/2005/06/08/hakmem-bit-count.aspx
 * counts the bits in a 32-bit integer "u" that are 1 in constant time and with
 * constant memory
 */
int bitCount(unsigned int u)                         
 {
         unsigned int uCount;
         uCount = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
	 
	 return ((uCount + (uCount >> 3)) & 030707070707) % 63;

 }


/*
 * counts the appearences of a given character "c" in the string in the
 * register "string"
 * returns -1 if there has been an error, and the number of appearences if
 * there has been no error
 */
int regCountChar(__m256i *string, char c)
{
	__m256i char_register = _mm256_set1_epi8(c);
	return bitCount(_mm256_movemask_epi8(_mm256_cmpeq_epi8(*string, char_register)));
}


/*
 * counts the appearences of a given character "c" in string "string" (with length
 * len_string)
 * returns -1 if there has been an error, and the number of appearences if
 * there has been no error
 */
int countCharPar(char * string, int len_string,  char c)
{
	int i, filler_size, count=0;
	char *filler_string;
	__m256i xmm;

	for ( i=0; i<=len_string-32; i+=32)
	{
		xmm = _mm256_load_si256((__m256i*) string);
		count += regCountChar(&xmm, c);
		string+=32;
	}

	// to avoid naughty memory access last chars treated different
	filler_size = len_string % 32;
	if (filler_size != 0)
	{
		filler_string = (char*) malloc(32*sizeof(char));
		// remaining chars into allocated 32 bytes memory
		strncpy(filler_string, string, filler_size);
		printf("%s\n", filler_string);
		xmm = _mm256_loadu_si256((__m256i*) filler_string);
		count += regCountChar(&xmm, c);

		free(filler_string);
	}
	return count;
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

void init_register() {
	// register with chars '<' than a
	lower_low_limit = _mm256_set1_epi8('`');
	// register with chars '>' than z
	upper_low_limit = _mm256_set1_epi8('{');
	// register with chars '<' than A
	lower_up_limit = _mm256_set1_epi8('@');
	// register with chars '>' than Z
	upper_up_limit = _mm256_set1_epi8('[');
	// register with the 8-bit values '32'
	register_of_32 = _mm256_set1_epi8(' ');
}



int no_main()
{
	char *test_word, *result_word;
	int count = 0;

	result_word = (char *) malloc(32 * sizeof(char));

	init_register();	

	test_word = rand_string_alloc(33);
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

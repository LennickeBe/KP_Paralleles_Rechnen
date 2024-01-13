#include <immintrin.h>  // intel intrinsics 
#include <string.h>	// string functions
#include <stdlib.h>	// string generation (rand_r)
#include <math.h>	// for "to the power of"
#include <stdint.h>	// for 64bit integer

#include "string_manipulation_par.h"

__m256i upper_low_limit;
__m256i lower_low_limit;
__m256i upper_up_limit;
__m256i lower_up_limit;
__m256i register_of_32;
__m256i c_register;
__m256i one_register;

/*
 * Turn string in register "string" to uppercase
 * returns 1 if there has been an error, 0 if there has been no error
 */
int regToUppercase(__m256i *string)
{
	// lower_low_limit is filled with 96 in 8-Bits
	// upper_low_limit is filled with 123 in 8-Bits
	// each 8-bit in string register is compared to both and
	// results in a register with ones where the 8bit number
	// is corresponds to a lowercase ascii char
	__m256i is_lower_char = _mm256_and_si256(
			_mm256_cmpgt_epi8(*string, lower_low_limit),
			_mm256_cmpgt_epi8(upper_low_limit, *string));

	// where ones are in the register we got from the comparison
	// we subtract 32 from the original number to transform into
	// uppercase
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

	// a register can hold 32 chars (8bit ints)
	// so we work on 32 chars of the string at a time
	for ( i=0; i<=len_string-32; i+=32)
	{
		xmm = _mm256_loadu_si256((__m256i*) string);
		regToUppercase(&xmm);
		_mm256_storeu_si256((__m256i*) string, xmm);
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
	// lower_up_limit is filled with 64 in 8-Bits
	// upper_up_limit is filled with 91 in 8-Bits
	// each 8-bit in string register is compared to both and
	// results in a register with ones where the 8bit number
	// is corresponds to a uppercase ascii char
	__m256i is_lower_char = _mm256_and_si256(
			_mm256_cmpgt_epi8(*string, lower_up_limit),
			_mm256_cmpgt_epi8(upper_up_limit, *string));

	// where ones are in the register we got from the comparison
	// we add 32 from the original number to transform into
	// lowercase
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

	// a register can hold 32 chars (8bit ints)
	// so we work on 32 chars of the string at a time
	for ( i=0; i<=len_string-32; i+=32)
	{
		xmm = _mm256_loadu_si256((__m256i*) string);
		regToLowercase(&xmm);
		_mm256_storeu_si256((__m256i*) string, xmm);
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
 * sums up the 64bit numbers in the given register
 */
int64_t sum_up_epi64(__m256i *counter)
{
	return (_mm256_extract_epi64(*counter, 0) +
		_mm256_extract_epi64(*counter, 1) +
		_mm256_extract_epi64(*counter, 2) +
		_mm256_extract_epi64(*counter, 3));
}


/*
 * sums up 8bit Blocks in groups of 8 in the lower 16 bits of 64bit Blocks
 * the resulting register is added to the given 64 bit register
 */
__m256i merge_epi8_to_epi64(__m256i *counter_epi64, __m256i *counter_epi8)
{
	return _mm256_add_epi64(*counter_epi64, 
			// this sums up 8bits into the lower 16bits of 64bit Blocks
			_mm256_sad_epu8(*counter_epi8, _mm256_setzero_si256()));
}


__m256i regCountChar(__m256i *string)
{
	return (_mm256_and_si256(_mm256_cmpeq_epi8(*string, c_register),
				one_register));
}

int64_t countCharPar(char *string, int len_string)
{
	int i, filler_size;
	char *filler_string;
	__m256i xmm, counter_epi8, counter_epi64;

	// in theory this function risks an overflow at the string length
	// (2^64-1) * 4 = 73.786.976.294.838.206.460
	// but the given len_string is an int which does not even go that far
	// so we assume only strings <= 2,147,483,647 are possible

	counter_epi8 = _mm256_setzero_si256();
	counter_epi64 = _mm256_setzero_si256();

	// a register can hold 32 chars (8bit ints)
	// so we work on 32 chars of the string at a time
	for ( i=0; i<=len_string-32; i+=32)
	{
		xmm = _mm256_loadu_si256((__m256i*) string);
		counter_epi8 = _mm256_add_epi8(counter_epi8, regCountChar(&xmm));

		// after 255 * 32 = 8160 steps the 8 bit could overflow
		if (!(i % 8160))
		{
			counter_epi64 = merge_epi8_to_epi64(&counter_epi64,
							&counter_epi8);
			counter_epi8 = _mm256_setzero_si256();
		}
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
		counter_epi8 = _mm256_add_epi8(counter_epi8, regCountChar(&xmm));

		free(filler_string);
	}
	
	// add remaining results
	counter_epi64 = merge_epi8_to_epi64(&counter_epi64, &counter_epi8);
	return sum_up_epi64(&counter_epi64);
}




/*
 * the register are used with the same content
 * so they are declared globaly and initialized here
 * the values are the limits for the lowercase
 * and uppercase ascii chars
 * as well as a register with 32 in each 8-bit
 */
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
	// register with the 8 bit values for 'c'
	c_register = _mm256_set1_epi8('c');
	// register with the 8 bit values 1
	one_register = _mm256_set1_epi8(1);
}

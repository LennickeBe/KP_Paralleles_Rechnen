#include <immintrin.h>  // intel intrinsics 
#include <string.h>	// string functions
#include <stdlib.h>	// string generation (rand_r)
#include <math.h>	// for "to the power of"

#include "string_manipulation_par.h"

__m256i upper_low_limit;
__m256i lower_low_limit;
__m256i upper_up_limit;
__m256i lower_up_limit;
__m256i register_of_32;
__m256i c_register;

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
int regCountChar(__m256i *string)
{
	return bitCount(_mm256_movemask_epi8(_mm256_cmpeq_epi8(*string, c_register)));
}


/*
 * counts the appearences of character "c" in string "string" (with length
 * len_string)
 * returns -1 if there has been an error, and the number of appearences if
 * there has been no error
 */
int countCharPar(char *string, int len_string)
{
	int i, filler_size, count=0;
	char *filler_string;
	__m256i xmm;

	// a register can hold 32 chars (8bit ints)
	// so we work on 32 chars of the string at a time
	for ( i=0; i<=len_string-32; i+=32)
	{
		xmm = _mm256_loadu_si256((__m256i*) string);
		count += regCountChar(&xmm);
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
		count += regCountChar(&xmm);

		free(filler_string);
	}
	return count;
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
}

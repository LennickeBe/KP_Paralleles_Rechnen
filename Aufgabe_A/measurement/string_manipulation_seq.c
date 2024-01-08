#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "string_manipulation_seq.h"

/*
 * Turn string "string" (with length len_string) to uppercase
 * returns 1 if there has been an error, 0 if there has been no error
 */
int toUppercaseSeq(char *string, int len_string)
{
	while(*string)
	{
		*string = toupper(*string);
		*string++;
	}
	return 0;
}


/*
 * Turn string "string" (with length len_string) to lowercase
 * returns 1 if there has been an error, 0 if there has been no error
 */
int toLowercaseSeq(char *string, int len_string)
{	
	while(*string)
	{
		*string = tolower(*string);
		*string++;
	}
	return 0;
}


/*
 * counts the appearences of character "c" in string "string" (with length
 * len_string)
 * returns -1 if there has been an error, and the number of appearences if
 * there has been no error
 */
int countCharSeq(char *string, int len_string)
{
	int count = 0;
	char c = 'c';
	while(*string)
	{
		if (strncmp(string, &c, 1) == 0)
		{
			count++;
		}
		*string++;
	}
	return count;
}

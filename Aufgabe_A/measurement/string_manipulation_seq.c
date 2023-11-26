#include <ctype.h>
#include <stdio.h>
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
 * counts the appearences of a given character "c" in string "string" (with length
 * len_string)
 * returns -1 if there has been an error, and the number of appearences if
 * there has been no error
 */
int countCharSeq(char *string, int len_string, char c)
{
	int count = 0;
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


void oof_main()
{
	char *test_word;
	int count;
	test_word = (char *) malloc(8*sizeof(char));
	strncpy(test_word, "classic", 8);

	printf("%s\n", test_word);
	toUppercaseSeq(test_word, 8);
	printf("%s\n", test_word);
	toLowercaseSeq(test_word, 8);
	printf("%s\n", test_word);

	count = countCharSeq(test_word, 8, 'c');
	printf("%d\n", count);
	
	free(test_word);
}

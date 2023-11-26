#ifndef STRING_MAN_PAR_H
#define STRING_MAN_PAR_H

#include <immintrin.h>
__m256i upper_low_limit;
__m256i lower_low_limit;
__m256i upper_up_limit;
__m256i lower_up_limit;
__m256i register_of_32;

void init_register();
int toUppercasePar(char *string, int len_string);
int toLowercasePar(char *string, int len_string);
int countCharPar(char *string, int len_string, char c);
#endif

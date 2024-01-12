#ifndef STRING_MAN_PAR_H
#define STRING_MAN_PAR_H

#include <stdint.h>

void init_register();
int toUppercasePar(char *string, int len_string);
int toLowercasePar(char *string, int len_string);
int64_t countCharPar(char *string, int len_string);
#endif

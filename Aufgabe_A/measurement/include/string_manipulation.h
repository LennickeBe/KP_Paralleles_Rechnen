#ifndef STRING_MANIPULATION_H
#define STRING_MANIPULATION_H

#include <time.h>

struct times {
	struct timespec (*starts)[];
	struct timespec (*ends)[];
	struct timespec *start;
	struct timespec *end;
};

#endif

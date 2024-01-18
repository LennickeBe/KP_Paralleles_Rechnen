#ifndef GOL_MAIN_H
#define GOL_MAIN_H

#include <time.h>

struct times {
	struct timespec (*starts)[];
	struct timespec (*ends)[];
	struct timespec *start;
	struct timespec *end;
};

#endif

#ifndef GOL_MAIN_H
#define GOL_MAIN_H

#include <time.h>


#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

#define THREADS_STR STRINGIFY(THREADS)
#define COMPILER_STR STRINGIFY(COMPILER)

struct times {
	struct timespec (*starts)[];
	struct timespec (*ends)[];
	struct timespec *start;
	struct timespec *end;
};

#endif

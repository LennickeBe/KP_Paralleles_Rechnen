#include <stdio.h>
#include <immintrin.h>
#include <string.h>
#include <math.h>


int random_int(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void main()
{
	int test = 0;

	printf("has %d\n", test);

}

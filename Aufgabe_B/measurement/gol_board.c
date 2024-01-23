#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

#include "gol_board.h"


bool board_compare(board *b1, board *b2)
{
	if (b1->rows != b2->rows) return false;
	if (b1->cols != b2->cols) return false;
	if (memcmp(b1->grid, b2->grid, b1->cols*b1->rows*sizeof(bool))) return false;
	return true;
}

board * create_board_copy(board *b)
{
	board *buf;
	size_t size = 2*sizeof(int) + (b->rows * b->cols) * sizeof(bool);
	buf = malloc(size);
	memcpy(buf, b, size);
	return buf;
}

void coords_on_board(board *b, int *x, int *y)
{
	if ( *x < 0 || *x >= b->cols)
	{
		*x = ( b->cols + *x ) % b->cols;
	}
	if ( *y < 0 || *y >= b->rows)
	{
		*y = ( b->rows + *y) % b->rows;
	}
}


bool check_state(board *b, int x, int y)
{
	coords_on_board(b, &x, &y);
	return b->grid[ y * b->cols + x];
}


void set_state (board *b, int x, int y, bool state)
{
	coords_on_board(b, &x, &y);
	b->grid[ y * b->cols + x ] = state;
}


int get_num_neighbours(board *b , int x, int y)
{
	return
	check_state(b, x-1, y-1) + check_state(b, x, y-1) + check_state(b, x+1, y-1) +
	check_state(b, x-1, y)   +                          check_state(b, x+1, y) +
	check_state(b, x-1, y+1) + check_state(b, x, y+1) + check_state(b, x+1, y+1);
}


bool get_new_state(board *b, int x, int y)
{
	int neighbours = get_num_neighbours(b, x, y);
	if (check_state(b, x, y))
	{
		if (neighbours < 2) return 0;
		if (neighbours > 3) return 0;
	}
	else
	{
		if ( neighbours == 3 ) return 1; 
	}
}


void update_board(board *b)
{
	int i, j;
	board *buf;
	buf = create_board_copy(b);
	int nthreads;
#pragma omp parallel for num_threads(THREADS) collapse(2)
	for ( i = 0; i < b->rows; i++)
	{
		for ( j = 0; j < b->cols; j++)
		{
			set_state(b, j, i, get_new_state(buf, j, i));
		}
	}
	free(buf); 
}


/*
 * returns a random int within the given range
 * utilizes the rand() method from math.h
 */
int random_int(int min, int max){
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}


board* init_board(int rows, int cols, int start_cells) 
{
	board *b = calloc(1, 2*sizeof(int) + (rows * cols) * sizeof(bool));
	b->rows = rows;
	b->cols = cols;


	if (start_cells)
	{
		#include <math.h>
		int i;
		for ( i = 0; i < start_cells; i++)
		{
			set_state(b, random_int(0,b->cols),
					random_int(0,b->rows),
					1);
		}
	}

	// Glider
	// 001
	// 101
	// 011
	else
	{
		set_state(b, 2, 0, 1);
		set_state(b, 0, 1, 1);
		set_state(b, 2, 1, 1);
		set_state(b, 1, 2, 1);
		set_state(b, 2, 2, 1);
	}
	return b;
}

#include <stdio.h>

#include "gol_board.h"

void create_pbm(board *b, char *filename)
{
    FILE *file;
    int i, j;
    
    file = fopen(filename, "wb");
    // magic number
    fprintf(file, "P1\n");
    // size
    fprintf(file, "%d %d\n", b->cols, b->rows);

    // loop over board for picture
    for ( i = 0; i < b-> rows; i++)
    {
        for ( j= 0; j < b->cols; j++)
        {
            fprintf(file, "%u", b->grid[ i * b->cols + j ]);
        }
        fprintf(file, "\n");
    }   
}
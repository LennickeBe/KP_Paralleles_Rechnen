#include <stdio.h>

#include "gol_board.h"

void create_pbm(board *b, char *filename)
{
    FILE *file;
    int i, j, x, y;

    // scaling factor
    int scale = 10;    


    file = fopen(filename, "wb");
    // magic number
    fprintf(file, "P1\n");
    // size
    fprintf(file, "%d %d\n", scale*b->cols, scale*b->rows);

    // loop over board for picture
    for ( i = 0; i < b->rows; i++)
    {
        for ( x=0;x<scale;x++)
        {
        for ( j= 0; j < b->cols; j++)
        {
            for(y=0;y<scale;y++)
            {
            fprintf(file, "%u", b->grid[ i * b->cols + j ]);
            }
        }
        fprintf(file, "\n");
        }
    }   
}
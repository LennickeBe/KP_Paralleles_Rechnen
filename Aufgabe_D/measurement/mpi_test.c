#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <gol_board.h>
#include <visualize.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    MPI_Init(NULL, NULL);

    // get information abouth the amount of nodes and which node we are in
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    board *b1, *b2;
    int rows = 8, cols = 8;
    bool row[cols];
    // creates a glider for all ranks
    b1 = init_board(rows, cols, 0);
    b2 = init_board(rows, cols, 50);

    if (world_rank==0) {
        create_pbm(b2, "pbms/start.pbm");
    }
    MPI_Scatter(
            b1->grid,
            cols,
            MPI_C_BOOL,
            row,
            cols,
            MPI_C_BOOL,
            0,
            MPI_COMM_WORLD
            );

    MPI_Barrier(MPI_COMM_WORLD);

    /*
    MPI_Gather(
            row,
            cols,
            MPI_C_BOOL,
            b2->grid,
            cols,
            MPI_C_BOOL,
            0,
            MPI_COMM_WORLD
            );
    */
    MPI_Allgather(
            row,
            cols,
            MPI_C_BOOL,
            b2->grid,
            cols,
            MPI_C_BOOL,
            MPI_COMM_WORLD
            );
    char filename[32];
    snprintf(filename, 32, "pbms/foo_%d_end.pbm", world_rank);
    create_pbm(b2, filename);

    MPI_Finalize();
    return 0;
}

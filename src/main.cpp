#include <iostream>
#include <mpi.h>
#include "island.h"
#include "utils.h"

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Assuming a 10x10 island for simplicity
    int island_size = 10;

    // Initialize Island object
    Island island(island_size);

    // Initialize island with initial populations and vegetation levels
    if (world_rank == 0) {
        island.initialize(100, 2, 1.0f);
    }

    // Broadcast island data to all processes
    MPI_Bcast(&island, sizeof(Island), MPI_BYTE, 0, MPI_COMM_WORLD);

    // Simulate the ecosystem
    island.simulate(100);

    MPI_Finalize();
    return 0;
}

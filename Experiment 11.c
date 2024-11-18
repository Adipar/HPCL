#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, N = 10000;
    int start, end, local_sum = 0, total_sum = 0;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Divide the range [1, N] among all processes
    int chunk_size = N / size;
    start = rank * chunk_size + 1;
    end = (rank == size - 1) ? N : start + chunk_size - 1;

    // Calculate the local sum for the assigned range
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }
    printf("Process %d: Calculated local sum = %d for range [%d, %d]\n", rank, local_sum, start, end);

    // Use MPI_Reduce to sum up all local sums at the root process
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Root process prints the total sum
    if (rank == 0) {
        printf("Total sum of first %d integers is: %d\n", N, total_sum);
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}

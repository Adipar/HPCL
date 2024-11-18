#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, n = 10000;
    int local_sum = 0, total_sum = 0;
    int chunk_size, start, end;
    int prev, next;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process and the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Calculate the chunk size and divide work among processes
    chunk_size = n / size;
    start = rank * chunk_size + 1;
    end = (rank == size - 1) ? n : start + chunk_size - 1;

    // Calculate the local sum for the assigned range
    for (int i = start; i <= end; i++) {
        local_sum += i;
    }
    printf("Process %d: Local sum = %d for range [%d, %d]\n", rank, local_sum, start, end);

    // Determine the neighboring ranks in a ring topology
    prev = (rank == 0) ? size - 1 : rank - 1;
    next = (rank == size - 1) ? 0 : rank + 1;

    // Use MPI point-to-point communication to send and receive partial sums in a ring
    if (rank != 0) {
        // Send the local sum to the next process
        MPI_Send(&local_sum, 1, MPI_INT, next, 0, MPI_COMM_WORLD);

        // Receive partial sum from the previous process
        MPI_Recv(&total_sum, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        // Root process (rank 0) doesn't send, it just waits for the total sum
        total_sum = local_sum;

        // Receive the sum from the last process in the ring (size-1) and accumulate
        MPI_Recv(&total_sum, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Finalize the sum (only the root process does this)
    if (rank == 0) {
        printf("Total sum of first %d integers is: %d\n", n, total_sum);
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Status status;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data[2]; // Array to hold two elements per process

    if (rank == 0) {
        // Root process
        printf("Root process: Waiting to receive data...\n");

        for (int i = 1; i < size; i++) {
            MPI_Recv(data, 2, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            printf("Root process received: %d and %d from process %d\n", data[0], data[1], i);
        }
    } else {
        // Non-root processes
        data[0] = rank * 2;       // Example element 1
        data[1] = rank * 2 + 1;   // Example element 2

        printf("Process %d sending: %d and %d to root process\n", rank, data[0], data[1]);
        MPI_Send(data, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}

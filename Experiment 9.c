#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Status status;
    char message[50];

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Root process
        printf("Root process: Hello World from process %d!\n", rank);

        // Receive messages from all other processes
        for (int i = 1; i < size; i++) {
            MPI_Recv(message, 50, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
            printf("Root process received: '%s' from process %d\n", message, i);
        }
    } else {
        // Non-root processes
        snprintf(message, 50, "Hello World from process %d", rank);
        printf("Process %d sending message to root process\n", rank);

        // Send message to the root process
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}

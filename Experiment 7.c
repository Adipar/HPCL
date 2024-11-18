#include <stdio.h>
#include <omp.h>

int main() {
    // Number of iterations in the loop
    int n = 16;
    // Define a chunk size
    int chunk = 4;

    // Print information about the program
    printf("Total iterations: %d\n", n);
    printf("Chunk size: %d\n", chunk);

    // Parallel loop with static scheduling
    #pragma omp parallel for schedule(static, chunk) num_threads(4)
    for (int i = 0; i < n; i++) {
        // Get the thread ID
        int thread_id = omp_get_thread_num();

        // Print the current iteration and the thread executing it
        printf("Iteration %d executed by thread %d\n", i, thread_id);
    }

    return 0;
}

#include <stdio.h>
#include <omp.h>

int main() {
    int n = 10; // Length of the series

    // Parallel region with 2 threads
    #pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();

        if (thread_id == 0) {
            // Thread 0 computes and prints the series of 2
            printf("Series of 2 by thread %d: ", thread_id);
            for (int i = 1; i <= n; i++) {
                printf("%d ", 2 * i);
            }
            printf("\n");
        } else if (thread_id == 1) {
            // Thread 1 computes and prints the series of 4
            printf("Series of 4 by thread %d: ", thread_id);
            for (int i = 1; i <= n; i++) {
                printf("%d ", 4 * i);
            }
            printf("\n");
        }
    }

    return 0;
}

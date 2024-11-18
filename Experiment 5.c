#include <stdio.h>
#include <omp.h>

int main() {
    int val = 1234;
    printf("Initial value of val: %d\n", val);

    #pragma omp parallel firstprivate(val) num_threads(4)
    {
        printf("Thread %d, initial val = %d\n", omp_get_thread_num(), val);
        val += 1;
        printf("Thread %d, updated val = %d\n", omp_get_thread_num(), val);
    }

    printf("Final value of val: %d\n", val);
    return 0;
}

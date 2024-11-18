#include <stdio.h>
#include <cuda_runtime.h>

#define N 512  // Size of the matrices

// CUDA kernel for matrix addition
__global__ void matrixAdd(int *A, int *B, int *C, int n) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;  // Calculate global thread index
    if (index < n) {
        C[index] = A[index] + B[index];  // Perform element-wise addition
    }
}

int main() {
    int *A, *B, *C;  // Matrices
    int *d_A, *d_B, *d_C;  // Device matrices

    int size = N * N * sizeof(int);  // Size of each matrix

    // Allocate memory for matrices on host
    A = (int *)malloc(size);
    B = (int *)malloc(size);
    C = (int *)malloc(size);

    // Initialize the matrices A and B with sample values
    for (int i = 0; i < N * N; i++) {
        A[i] = i;
        B[i] = i * 2;
    }

    // Allocate memory for matrices on device
    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);
    cudaMalloc((void **)&d_C, size);

    // Copy matrices from host to device
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    // Define block and grid size
    int blockSize = 256;
    int numBlocks = (N * N + blockSize - 1) / blockSize;

    // Launch the kernel
    matrixAdd<<<numBlocks, blockSize>>>(d_A, d_B, d_C, N * N);

    // Copy the result matrix from device to host
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    // Print the result (only first 10 elements for brevity)
    printf("Matrix A + B (first 10 elements):\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", C[i]);
    }
    printf("\n");

    // Free device memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    // Free host memory
    free(A);
    free(B);
    free(C);

    return 0;
}

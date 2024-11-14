#include "cumm.cuh"

#define THREAD_DIM 16


size_t cdiv(size_t total, size_t size){
    return (total + size - 1) / size;
}

__global__ void multiply_kernel(double *matA, double *matB, double *matC, int m, int k, int n){
    __shared__ double sharedA[THREAD_DIM][THREAD_DIM];
    __shared__ double sharedB[THREAD_DIM][THREAD_DIM];

    int row = blockIdx.x * blockDim.x + threadIdx.x;
    int col = blockIdx.y * blockDim.y + threadIdx.y;

    double res = 0.;
    for (int tile = 0; tile < k; tile += THREAD_DIM){
        int colA = tile + threadIdx.y;
        int rowB = tile + threadIdx.x;
        sharedA[threadIdx.x][threadIdx.y] = (colA < k && row < m)? matA[row * k + colA]: 0.;
        sharedB[threadIdx.x][threadIdx.y] = (rowB < k && col < n)? matB[rowB * n + col]: 0.;
        __syncthreads();
        for (int i = 0; i < THREAD_DIM; i++)
            res += sharedA[threadIdx.x][i] * sharedB[i][threadIdx.y];
        __syncthreads();
    }

    if (row < m && col < n)
        matC[row * n + col] = res;
}

Matrix multiply_cuda(const Matrix &A, const Matrix &B){
    if (A.ncol() != B.nrow())
        throw std::runtime_error("A.ncol() does not equal to B.nrow().");
        
    Matrix C(A.nrow(), B.ncol());

    double *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, A.buffer_size());
    cudaMalloc(&d_B, B.buffer_size());
    cudaMalloc(&d_C, C.buffer_size());

    cudaMemcpy(d_A, A.data_ptr(), A.buffer_size(), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B.data_ptr(), B.buffer_size(), cudaMemcpyHostToDevice);

    size_t m = A.nrow(), k = A.ncol(), n = B.ncol();
    dim3 thread_dims(THREAD_DIM, THREAD_DIM);
    dim3 block_dims(cdiv(m, THREAD_DIM), cdiv(n, THREAD_DIM));
    multiply_kernel<<<block_dims, thread_dims>>>(d_A, d_B, d_C, m, k, n);

    cudaMemcpy(C.data_ptr(), d_C, C.buffer_size(), cudaMemcpyDeviceToHost);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    return C;
}
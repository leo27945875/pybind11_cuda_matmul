#include <iostream>
#include "mm.hpp"
#include "cumm.cuh"


#define SIZE 16
#define MAT_TOTAL 16 * 16


int main(){
    Matrix A(SIZE, SIZE);
    Matrix B(SIZE, SIZE);
    Matrix C(SIZE, SIZE);
    Matrix D(SIZE, SIZE);

    A.rand_init();
    B.rand_init();
    C = multiply_naive(A, B);
    D = multiply_cuda(A, B);

    C.show();
    D.show();

    std::cout << "\n" << (C.is_close(D)? "Equal": "Not equal") << std::endl;

    return 0;
}
#include <iostream>
#include "mm.hpp"
#include "cumm.cuh"


#define H 153
#define K 101
#define W 192


int main(){
    Matrix A(H, K);
    Matrix B(K, W);
    Matrix C(H, W);
    Matrix D(H, W);

    A.rand_init();
    B.rand_init();
    C = multiply_naive(A, B);
    D = multiply_cuda(A, B);

    // std::cout << std::endl;
    // C.show();
    // D.show();

    std::cout << "\n" << (C.is_close(D)? "Equal": "Not equal") << std::endl;

    return 0;
}
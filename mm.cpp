#include "mm.hpp"


Matrix multiply_naive(const Matrix &A, const Matrix &B){
    if (A.ncol() != B.nrow())
        throw std::runtime_error("A.ncol() does not equal to B.nrow().");
        
    Matrix C(A.nrow(), B.ncol());
    for (size_t i = 0; i < A.nrow(); i++){
    for (size_t j = 0; j < B.ncol(); j++){
    for (size_t k = 0; k < B.nrow(); k++){
        C(i, j) += A(i, k) * B(k, j);
    }}}
    return C;
}


Matrix multiply_tile(const Matrix &A, const Matrix &B, size_t tile){
    if (A.ncol() != B.nrow())
        throw std::runtime_error("A.ncol() does not equal to B.nrow().");
        
    Matrix C(A.nrow(), B.ncol());
    for (size_t ti = 0; ti < A.nrow(); ti+=tile)
    for (size_t tj = 0; tj < B.ncol(); tj+=tile)
    for (size_t tk = 0; tk < B.nrow(); tk+=tile){
        size_t i_end = std::min(ti + tile, A.nrow());
        size_t j_end = std::min(tj + tile, B.ncol());
        size_t k_end = std::min(tk + tile, B.nrow());
        for (size_t i = ti; i < i_end; i++)
        for (size_t j = tj; j < j_end; j++)
        for (size_t k = tk; k < k_end; k++)
            C(i, j) += A(i, k) * B(k, j);
    }
    return C;
}

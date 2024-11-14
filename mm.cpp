#include "mm.hpp"


Matrix multiply_naive(const Matrix &A, const Matrix &B){
    Matrix C(A.nrow(), B.ncol());
    for (size_t i = 0; i < A.nrow(); i++){
        for (size_t j = 0; j < B.ncol(); j++){
            for (size_t k = 0; k < B.nrow(); k++){
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    return C;
}


Matrix multiply_tile(const Matrix &A, const Matrix &B, size_t tile){
    Matrix C(A.nrow(), B.ncol());
    for (size_t ti = 0; ti < A.nrow(); ti+=tile)
    for (size_t tj = 0; tj < B.ncol(); tj+=tile)
    for (size_t tk = 0; tk < B.nrow(); tk+=tile)
    for (size_t i = ti; i < ti + tile && i < A.nrow(); i++){
        for (size_t j = tj; j < tj + tile && j < B.ncol(); j++){
            for (size_t k = tk; k < tk + tile && k < B.nrow(); k++){
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    return C;
}

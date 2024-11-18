#pragma once

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <string.h>
#include <cmath>


class Matrix {
public:
    Matrix(size_t nrow, size_t ncol)
        : m_nrow(nrow), m_ncol(ncol), m_buffer(new double[nrow * ncol])
    {
        memset(m_buffer, 0, nrow * ncol * sizeof(double));
    }
    Matrix(const Matrix& other)
        : m_nrow(other.nrow()), m_ncol(other.ncol())
    {
        size_t n_elem = m_nrow * m_ncol;
        m_buffer = new double[n_elem];
        memcpy(m_buffer, other.data_ptr(), n_elem * sizeof(double));
    }
    ~Matrix()
    {
        delete[] m_buffer;
    }

    Matrix& operator=(const Matrix& other){
        delete[] m_buffer;
        m_nrow = other.nrow();
        m_ncol = other.ncol();
        size_t n_elem = m_nrow * m_ncol;
        m_buffer = new double[n_elem];
        memcpy(m_buffer, other.data_ptr(), n_elem * sizeof(double));
        return *this;
    }
    bool operator==(const Matrix& other) const {
        if (m_nrow != other.nrow() || m_ncol != other.ncol())
            return false;
        for (size_t i = 0; i < m_nrow; i++)
        for (size_t j = 0; j < m_ncol; j++)
            if (this->operator()(i, j) != other(i, j))
                return false;
        return true;
    }
    double operator() (size_t row, size_t col) const
    {
        return m_buffer[row*m_ncol + col];
    }
    double & operator() (size_t row, size_t col)
    {
        return m_buffer[row*m_ncol + col];
    }

    double   get(size_t row, size_t col) const { return this->operator()(row, col); }
    double & set(size_t row, size_t col)       { return this->operator()(row, col); }

    size_t nrow() const { return m_nrow; }
    size_t ncol() const { return m_ncol; }
    double * data_ptr() const { return m_buffer; }

    size_t buffer_size() const { 
        return m_nrow * m_ncol * sizeof(double); 
    }
    bool is_out(size_t row, size_t col) const { 
        return row >= m_nrow || col >= m_ncol; 
    }
    bool is_close(const Matrix& other, double tol = 1e-5) const {
        bool res = true;
        for (size_t i = 0; i < nrow(); i++)
            for (size_t j = 0; j < ncol(); j++)
                res = res && abs(this->operator()(i, j) - other(i, j)) < tol;
        return res;
    }
    void show() const {
        std::cout << "Matrix Elems:" << std::endl;
        for (size_t i = 0; i < nrow(); i++){
            for (size_t j = 0; j < ncol(); j++)
                std::cout << this->operator()(i, j) << " ";
            std::cout << std::endl;
        }
    }
    void rand_init(){
        for (size_t i = 0; i < nrow(); i++)
            for (size_t j = 0; j < ncol(); j++)
                this->operator()(i, j) = ((float)(rand()) / (float)(RAND_MAX)) * 2. - 1.;
    }

private:
    size_t m_nrow;
    size_t m_ncol;
    double *m_buffer;
};



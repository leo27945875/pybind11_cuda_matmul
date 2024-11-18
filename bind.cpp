#include <pybind11/pybind11.h>
#include "mm.hpp"
#include "cumm.cuh"

namespace py = pybind11;

PYBIND11_MODULE(_matrix, m){
    py::class_<Matrix>(m, "Matrix")
        .def(py::init<size_t, size_t>())
        .def("__getitem__", [](Matrix &self, std::pair<size_t, size_t> key){ return self(key.first, key.second); })
        .def("__setitem__", [](Matrix &self, std::pair<size_t, size_t> key, double val){ self(key.first, key.second) = val; })
        .def("__eq__", &Matrix::operator==)
        .def("show", &Matrix::show)
        .def("is_close", &Matrix::is_close)
        .def("data_ptr", &Matrix::data_ptr)
        .def_property("nrow", &Matrix::nrow, nullptr)
        .def_property("ncol", &Matrix::ncol, nullptr);

    m.def("multiply_naive", &multiply_naive, py::arg("A"), py::arg("B"));
    m.def("multiply_tile" , &multiply_tile , py::arg("A"), py::arg("B"), py::arg("tile"));
    m.def("multiply_cuda" , &multiply_cuda , py::arg("A"), py::arg("B"));
}
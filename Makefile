NAME := _matrix$(shell python3-config --extension-suffix)

test:
	python -m unittest

testcpp:  test_matrix.cpp mm.cpp cumm.cu matrix.hpp mm.hpp cumm.cuh
	nvcc test_matrix.cpp mm.cpp cumm.cu -o test_matrix
	./test_matrix

clean:
	rm -rf ${NAME} __pycache__ build/* test_matrix
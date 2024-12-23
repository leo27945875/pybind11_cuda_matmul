import timeit
import sys
import _matrix


class Writer:
    def __init__(self, streams):
        self.streams = streams

    def write(self, msg):
        for stream in self.streams:
            stream.write(msg)


def benchmark():

    setup = '''
import _matrix

size = 1000
tile_size = 64

mat1 = _matrix.Matrix(size,size)
mat2 = _matrix.Matrix(size,size)

for it in range(size):
    for jt in range(size):
        mat1[it, jt] = it * size + jt + 1
        mat2[it, jt] = it * size + jt + 1
'''

    naive = timeit.Timer('_matrix.multiply_naive(mat1, mat2)', setup=setup)
    cuda = timeit.Timer('_matrix.multiply_cuda(mat1, mat2)', setup=setup)
    tile = timeit.Timer('_matrix.multiply_tile(mat1, mat2, tile_size)', setup=setup)

    repeat = 5

    with open('performance.txt', 'w') as fobj:

        w = Writer([sys.stdout, fobj])

        w.write(f'Start multiply_naive (repeat={repeat}), take min = ')
        naivesec = minsec = min(naive.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_tile (repeat={repeat}), take min = ')
        tilesec = minsec = min(tile.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write(f'Start multiply_cuda (repeat={repeat}), take min = ')
        cudasec = minsec = min(cuda.repeat(repeat=repeat, number=1))
        w.write(f'{minsec} seconds\n')

        w.write('Tile speed-up over Naive: %g x\n' % (naivesec/tilesec))
        w.write('CUDA speed-up over naive: %g x\n' % (naivesec/cudasec))


if __name__ == '__main__':

    benchmark()
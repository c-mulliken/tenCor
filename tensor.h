#include <stdlib.h>

typedef struct {
    int* shape;
    float* data;
    int* strides;

    int ndim;
    int itemsize;
    int size;
} Tensor;

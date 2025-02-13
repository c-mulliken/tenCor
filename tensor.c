#include <stdlib.h>
#include <stdio.h>

#include "tensor.h"

void computeStrides(Tensor* tensor) {
    // Give Tensor tensor, update strides based on shape
    tensor->strides = (int*)malloc(tensor->ndim * sizeof(int));
    int stride = 1;
    for (int i = tensor->ndim - 1; i >= 0; i--) {
        tensor->strides[i] = stride;
        stride *= tensor->shape[i];
    }
}

void computeSize(Tensor* tensor) {
    int size = 1;
    for (int i = tensor->ndim - 1; i >= 0; i--) {
        size *= tensor->shape[i];
    }
    tensor->size = size;
}

Tensor* createTensor(int* shape, int ndim) {
    Tensor* tensor = (Tensor*)malloc(sizeof(Tensor));
    memcpy(tensor->shape, shape, ndim * sizeof(int));
    tensor->ndim = ndim;
    computeStrides(tensor);
    computeSize(tensor);
    tensor->data = (float*)malloc(tensor->size * sizeof(float));
    return tensor;
}

void freeTensor(Tensor* tensor) {
    free(tensor->shape);
    free(tensor->data);
    free(tensor->strides);
    free(tensor);
}

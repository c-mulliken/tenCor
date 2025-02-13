#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    tensor->shape = (int*)malloc(ndim * sizeof(int));
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

int getFlatIndex(int* indices, Tensor* tensor) {
    int idx = 0;
    for (int i = 0; i < tensor->ndim; i++) {
        idx += tensor->strides[i] * indices[i];
    }
    return idx;
} 

void setOneValue(float value, int* indices, Tensor* tensor) {
    int idx = getFlatIndex(indices, tensor);
    tensor->data[idx] = value;
}

void initOnes(Tensor* tensor) {
    for (int i = 0; i < tensor->size; i++) {
        tensor->data[i] = 1.0;
    }
}

void initZeroes(Tensor* tensor) {
    for (int i = 0; i < tensor->size; i++) {
        tensor->data[i] = 0.0;
    }
}

void initRand(Tensor* tensor) {
    for (int i = 0; i < tensor->size; i++) {
        tensor->data[i] = (float)rand() / (float)RAND_MAX;
    }
}

void printTensor(Tensor* tensor) {
    if (tensor->ndim > 2) {
        printf("WARNING: Printing unimplemented for ndim > 2.\n");
    } else {
        printf("[\n");
        for (int i = 0; i < tensor->shape[0]; i++) {
            printf("[");
            for (int j = 0; j < tensor->shape[1]; j++) {
                int indices[2] = {i, j};
                float value = tensor->data[getFlatIndex(indices, tensor)];
                printf("%.3f ", value);
            }
            printf("]\n");
        }
        printf("]\n");
    }
}

int checkEqualShapes(int* shape1, int* shape2, int ndim) {
    for (int i = 0; i < ndim; i++) {
        if (shape1[i] != shape2[i]) {
            return 0;
        }
    }
    return 1;
}

Tensor* addTensors(Tensor* t1, Tensor* t2) {
    if (t1->ndim != t2->ndim) {
        printf("ERROR: Dimensions don't match.\n");
        return NULL;
    } else if (!checkEqualShapes(t1->shape, t2->shape, t1->ndim)) {
        printf("ERROR: Shapes don't match.\n");
        return NULL;
    }

    Tensor* out_tensor = createTensor(t1->shape, t1->ndim);
    for (int i = 0; i < t1->size; i++) {
        out_tensor->data[i] = t1->data[i] + t2->data[i];
    }
    return out_tensor;
}

Tensor* negateTensor(Tensor* tensor) {
    Tensor* out_tensor = createTensor(tensor->shape, tensor->ndim);
    for (int i = 0; i < tensor->size; i++) {
        out_tensor->data[i] = -(tensor->data[i]);
    }
    return out_tensor;
}

int main() {
    int shape[2] = {5, 5};
    Tensor* t1 = createTensor(shape, 2);
    Tensor* t2 = createTensor(shape, 2);
    initOnes(t1);
    initRand(t2);
    Tensor* t3 = negateTensor(t2);
    printTensor(t1);
    printTensor(t3);
    Tensor* t = addTensors(t1, t3);
    printTensor(t);
    freeTensor(t1);
    freeTensor(t2);
    freeTensor(t3);
    freeTensor(t);
    return 0;
}

# 4FUN

# compile

```bash
#!/bin/bash

module load nvhpc/25.9 openblas/0.3.30

rm -rf TEST

cp -r 4FUN/ TEST

mkdir TEST/build && mkdir TEST/INSTALL

cd TEST/

cmake -S  ./ -B build/ -DCMAKE_INSTALL_PREFIX=/home/wuxian/Work/github/TEST/INSTALL -DCMAKE_BUILD_TYPE=Release --fresh

```

# test file vecadd.cu

```bash
export PREFIX=/home/wuxian/Work/github/TEST/INSTALL
nvcc -O3 -arch=sm_86 -Xcompiler -Wall --ptxas-options=-v -I$PREFIX/include/4fun -L$PREFIX/lib -l4fun_gpu -l4fun_utils vecadd.cu -o run
```


```c
#include "gpu_cblas_lvl1_d.h"   // installed header
#include "handle_gpu_error.h"

int main (){
    int ierr  = 0;
    const int n = 4;
    const size_t arraySize = n * sizeof(double);
    double x[n] = {1., 2., 3., 4.};
    double y[n] = {5., 6., 7., 8.};
    double HostRef[n] = {0., 0., 0., 0.};
    double alpha = 1.0;
    double *d_x = NULL;
    double *d_y = NULL;

    for(int i=0; i<n; ++i){
        HostRef[i] = alpha*x[i] + y[i];
        printf("HostRef[%d] = %f \n", i, HostRef[i]);
    }

    gpu_errchk(cudaMalloc((void**)&d_x, arraySize));
    gpu_errchk(cudaMalloc((void**)&d_y, arraySize));
    gpu_errchk(cudaMemcpy(d_x, x, arraySize, cudaMemcpyHostToDevice));
    gpu_errchk(cudaMemcpy(d_y, y, arraySize, cudaMemcpyHostToDevice));

    dim3 threadsPerBlock = (4);
    dim3 numBlocks = (n + threadsPerBlock.x - 1) / threadsPerBlock.x;

    gpu_daxpy<<<numBlocks, threadsPerBlock>>>(n, alpha, d_x, d_y);

    gpu_errchk(cudaMemcpy(y, d_y, arraySize, cudaMemcpyDeviceToHost));

    for(int i=0; i<n; ++i){
        printf("device[%d] = %f \n", i, y[i]);
    }

    gpu_errchk(cudaFree(d_x));d_x=NULL;
    gpu_errchk(cudaFree(d_y));d_y=NULL;

    return ierr;
}

```

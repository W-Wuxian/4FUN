#include "gpu_cblas_lvl1_d.h"
#include "handle_gpu_error.h"
#include "handle_matgen.h"
#include "handle_showmat.h"

#ifndef MIN_LEN
#define MIN_LEN 1
#endif

#ifndef MAX_LEN
//#define MAX_LEN 10000000
#define MAX_LEN 10
#endif

int main (){
    int ierr  = 0;

    #if defined(FIXSEED)
    #define WSRAND
    srand(FIXSEED);
    #elif defined(RANDSEED)
    #define WSRAND
    srand(time(0));
    #endif

    int N = MAX_LEN;
    #if defined(WSRAND)
    N = genRandIntWithRange(MAX_LEN, MIN_LEN);
    #endif
    size_t arraySize = sizeof(MYTYPE) * N;
    MYTYPE alpha = (MYTYPE)1;

    // Allocate and initialize arrays on the Host
    MYTYPE* x = (MYTYPE*) malloc(arraySize);
    MYTYPE* y = (MYTYPE*) malloc(arraySize);
    MYTYPE* HostRef = (MYTYPE*) malloc(arraySize);
    genRandArrayWithinBounds(x, N);
    genRandArrayWithinBounds(y, N);
    memset(HostRef, 0, arraySize);

    // Allocate and initialize arrays on the Device
    MYTYPE *d_x = NULL;
    MYTYPE *d_y = NULL;
    
    WICHTYPE();
    #ifdef WSRAND
    printf("With random seed\n");
    #endif

    for(int i=0; i<N; ++i){HostRef[i] = alpha * x[i] + y[i];}
    
    if(N<11){
        showMat( HostRef, 1, N, "HostRef\0" );
    }

    gpu_errchk(cudaMalloc((void**)&d_x, arraySize));
    gpu_errchk(cudaMalloc((void**)&d_y, arraySize));
    gpu_errchk(cudaMemcpy(d_x, x, arraySize, cudaMemcpyHostToDevice));
    gpu_errchk(cudaMemcpy(d_y, y, arraySize, cudaMemcpyHostToDevice));

    dim3 threadsPerBlock = (16);
    dim3 numBlocks = (N + threadsPerBlock.x - 1) / threadsPerBlock.x;

    gpu_daxpy<<<numBlocks, threadsPerBlock>>>(N, alpha, d_x, d_y);

    gpu_errchk(cudaMemcpy(y, d_y, arraySize, cudaMemcpyDeviceToHost));

    if(N<11){showMat( y, 1, N, "device result\0" );}

    gpu_errchk(cudaFree(d_x));d_x=NULL;
    gpu_errchk(cudaFree(d_y));d_y=NULL;
    free(x);x = NULL;
    free(y);y = NULL;
    free(HostRef);HostRef = NULL;

    return ierr;
}
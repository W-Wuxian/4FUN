#include "gpu_cblas_lvl1_d.h"

__global__ void
gpu_daxpy( const int n, const double alpha, const double *device_x, double *device_y )
{
    int ID = threadIdx.x + blockIdx.x * blockDim.x;  // Global index

    if ( ID < n ) {
        device_y[ID] += alpha * device_x[ID];
    }
}
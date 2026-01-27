#ifndef __GPU_CBLAS_LVL1_D_H__
#define __GPU_CBLAS_LVL1_D_H__

#include "define_type.h"

// cblas_daxpy y := a*x + y
__global__ void gpu_daxpy(const int n, const double alpha, const double *device_x, const int incx, double *device_y, const int incy);

#endif //__GPU_CBLAS_LVL1_D_H__

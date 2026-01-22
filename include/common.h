#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef WITH_CUDA
#include <cuda_runtime.h>
#endif

#ifdef WITH_CBLAS
#include "cblas.h"
#elif WITH_CUSTOM_CBLAS
#include "./custom_cblas/custom_cblas.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE  // Required for RUSAGE_THREAD on Linux
#endif
#include <sys/resource.h>  // struct rusage, getrusage(), RUSAGE_THREAD
#include <sys/time.h>      // struct timeval (ru_utime fields)

#endif  //__COMMON_H__

#ifndef __HANDLE_GPU_ERROR_H__
#define __HANDLE_GPU_ERROR_H__

// https://gist.github.com/raytroop/120e2d175d95f82edbee436374293420
// https://stackoverflow.com/questions/14038589/what-is-the-canonical-way-to-check-for-errors-using-the-cuda-runtime-api
#ifdef WDEBUG
#define gpu_errchk( ans )                                                                          \
    {                                                                                              \
        gpu_assert( ( ans ), __FILE__, __LINE__ );                                                 \
    }
#else
#define gpu_errchk( ans )                                                                          \
    {                                                                                              \
        ( ans );                                                                                   \
    }
#endif

void
gpu_assert( cudaError_t code, const char *file, int line, bool abort = true )

#endif  //__HANDLE_GPU_ERROR_H__

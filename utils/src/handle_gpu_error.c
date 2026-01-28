#include "handle_gpu_error.h"

/**
 * @brief GPU error handling function
 *
 * @param code   Error code returned by CUDA API call
 * @param file   File name where the error occurred
 * @param line   Line number in the file where the error occurred
 *
 */
inline void
gpuAssert( cudaError_t code, const char *file, int line )
{
    if ( code != cudaSuccess ) {
        fprintf( stderr, "gpu_assert: %s %s %d\n", cudaGetErrorString( code ), file, line );
        exit( code );
    }
}
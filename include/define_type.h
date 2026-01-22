#ifndef __HANDLE_TYPE_H__
#define __HANDLE_TYPE_H__

#include "common.h"

#ifdef USE_FLOAT
#define MYTYPE float
#define MYTYPE_FLOAT  // Active le bon cas
#ifdef WITH_CBLAS
#define cblas_xgemm cblas_sgemm
#define cblas_xcopy cblas_scopy
#define cblas_xaxpy cblas_saxpy
#define cblas_xomatcopy cblas_somatcopy
#endif  // WITH_CBLAS
#define WICHTYPE() printf( "Using float\n" )
#elif USE_DOUBLE
#define MYTYPE double
#define MYTYPE_DOUBLE  // Active le bon cas
#ifdef WITH_CBLAS
#define cblas_xgemm cblas_dgemm
#define cblas_xcopy cblas_dcopy
#define cblas_xaxpy cblas_daxpy
#define cblas_xomatcopy cblas_domatcopy
#endif  // WITH_CBLAS
#define WICHTYPE() printf( "Using double\n" )
#else
#define MYTYPE double  // Default: Double
#ifdef WITH_CBLAS
#define cblas_xgemm cblas_dgemm
#define cblas_xcopy cblas_dcopy
#define cblas_xaxpy cblas_daxpy
#define cblas_xomatcopy cblas_domatcopy
#endif  // WITH_CBLAS
#define WICHTYPE() printf( "Using double\n" )
#endif

#define MAX( a, b )                                                                                \
    ( {                                                                                            \
        __typeof__( a ) _a = ( a );                                                                \
        __typeof__( b ) _b = ( b );                                                                \
        _a > _b ? _a : _b;                                                                         \
    } )

#define MIN( a, b )                                                                                \
    ( {                                                                                            \
        __typeof__( a ) _a = ( a );                                                                \
        __typeof__( b ) _b = ( b );                                                                \
        _a < _b ? _a : _b;                                                                         \
    } )

#endif  //__HANDLE_TYPE_H__

#ifndef __HANDLE_MATGEN_H__
#define __HANDLE_MATGEN_H__

#include "define_type.h"

int  genRandIntWithRange( int max_len, int min_len );
void genRandMatWithRangeR1R2( int ( *fptr )( int, int ),
                              MYTYPE *mat,
                              int     nrow,
                              int     ncol,
                              int     r1,
                              int     r2 );
void genRandArrayWithinBounds( void *A, int N );

#endif  //__HANDLE_MATGEN_H__

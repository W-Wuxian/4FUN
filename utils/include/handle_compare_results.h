#ifndef __HANDLE_COMPARE_RESULTS_H__
#define __HANDLE_COMPARE_RESULTS_H__

#include "define_type.h"

#ifdef __cplusplus
extern "C" {
#endif

void compareHostDevice( const MYTYPE *Host, const MYTYPE *Device, const int rows, const int cols );
void checkTranspose( const MYTYPE *input, MYTYPE *output, int rows, int cols );

#ifdef __cplusplus
}
#endif


#endif  //__HANDLE_COMPARE_RESULTS_H__

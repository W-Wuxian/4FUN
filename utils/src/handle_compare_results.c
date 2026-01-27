#include "../include/handle_compare_results.h"

/**
 * @brief Compares host and device result computation for mismatches.
 * 
 * This function iterates over the host and device arrays, comparing corresponding elements. If a mismatch is detected,
 * it prints an error message to stdout with details on the location of the mismatch.
 *
 * The function uses relative tolerance (rtol) and absolute tolerance (atol) values that are defined based on the type
 * being used (MYTYPE). These tolerances are scaled to be around 5-10 times the epsilon value for the respective type.
 *
 * @param Host Pointer to host memory array (result from CPU kernel).
 * @param Device Pointer to device memory array (result from GPU kernel).
 * @param rows Number of rows in the arrays.
 * @param cols Number of columns in the arrays.
 */
void compareHostDevice(const MYTYPE* Host, const MYTYPE* Device, const int rows, const int cols){
    int mismatches = 0;
    // Type-specific tolerances (scale ~5-10× epsilon)
    #if defined(MYTYPE_FLOAT)
        const MYTYPE rtol = 1e-4f;
        const MYTYPE atol = 1e-6f;
    #elif defined(MYTYPE_DOUBLE)
        const MYTYPE rtol = 1e-6;
        const MYTYPE atol = 1e-12;
    #else
        const MYTYPE rtol = 1e-6;
        const MYTYPE atol = 1e-12;
    #endif
    for(int i = 0 ; i < rows; i++){
        int offset = i * cols;
        for (int j = 0; j < cols; ++j) {
            int k=j + offset;
            if (fabs(Host[k] - Device[k]) > rtol * (fabs(Host[k]) + fabs(Device[k]) + atol)) {
                printf("mismatch (%d,%d): host=%.17g device=%.17g rel_err=%g\n",
                       i, j, Host[k], Device[k], fabs(Host[k]-Device[k]) / (fabs(Host[k])+atol));
                mismatches++;
                if(mismatches >= 10) { printf("ABORT: >10 mismatches\n"); return; }
            }
        }
    }
    printf("%s: %d mismatches\n", mismatches ? "FAILED" : "PASSED", mismatches);
}

/**
 * @brief Check the transpose of a matrix.
 * 
 * @param input matrix to check the transpose of.
 * @param output matrix to store the transposed input.
 * @param rows number of rows in the input matrix.
 * @param cols number of columns in the input matrix.
 */
void checkTranspose(const MYTYPE* input, MYTYPE* output, int rows, int cols){
    int mismatches = 0;
    // Type-specific tolerances (scale ~5-10× epsilon)
    #if defined(MYTYPE_FLOAT)
        const MYTYPE rtol = 1e-4f;
        const MYTYPE atol = 1e-6f;
    #elif defined(MYTYPE_DOUBLE)
        const MYTYPE rtol = 1e-6;
        const MYTYPE atol = 1e-12;
    #else
        const MYTYPE rtol = 1e-6;
        const MYTYPE atol = 1e-12;
    #endif
    for(int i=0; i<rows; i++){
        int in_offset = i * cols;
        for(int j=0; j<cols; j++){
            int in_ID = in_offset + j;
            int out_offset = j*rows;
            int out_ID = out_offset + i;
            if (fabs(input[in_ID] - output[out_ID]) > rtol * (fabs(input[in_ID]) + fabs(output[out_ID]) + atol)) {
                printf("mismatch (%d,%d): host=%.17g device=%.17g rel_err=%g\n",
                       i, j, input[in_ID], output[out_ID], fabs(input[in_ID]-output[out_ID]) / (fabs(input[in_ID])+atol));
                mismatches++;
                if(mismatches >= 10) { printf("ABORT: >10 mismatches\n"); return; }
            }
        }
    }
    printf("%s: %d mismatches\n", mismatches ? "FAILED" : "PASSED", mismatches);
}

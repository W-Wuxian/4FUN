#include "../include/handle_matgen.h"

/**
 * @brief Generate a random integer between two values.
 *
 * This function generates a random integer within the specified range
 * [min_len, max_len]. It uses the rand() function to generate a random number.
 * 
 * @param max_len 
 * @param min_len 
 * @return int 
 */
int genRandIntWithRange(int max_len, int min_len){
    return (rand() % (max_len - min_len + 1)) + min_len;
}

/**
 * @brief Fill an object type like matrix with random values from the range [r1, r2].
 * 
 * @param fptr Pointer to the function that generates random values
 * @param mat Pointer to the object type like matrix where the values will be stored
 * @param nrow Number of rows in the matrix
 * @param ncol Number of columns in the matrix
 * @param r1 lower range 
 * @param r2 upper range
 */
void genRandMatWithRangeR1R2(int (*fptr)(int, int), MYTYPE* mat, int nrow, int ncol, int r1, int r2){
    size_t nelems = nrow*ncol;
    for (size_t i = 0; i < nelems; ++i) {
        mat[i] = (MYTYPE)fptr(MAX(r1,r2), MIN(r1, r2));
    }
}

/**
 * @brief Fill an object like array with random values from [0, N)
 * 
 * @param A Object like array to be filled
 * @param N product of the dimensions of A
 */
void genRandArrayWithinBounds(void* A, int N) {
    for (int i = 0; i < N; ++i){
        MYTYPE x = ((MYTYPE)rand()/(MYTYPE)(RAND_MAX)) * N;
        ((MYTYPE*)A)[i] = x;
    }
}
#include "handle_showmat.h"

/**
 * @brief Show the matrix in a readable format.
 *
 * This function prints the given matrix to the console, displaying its dimensions
 * and its tag name.
 * 
 * @param mat Pointer to the matrix data
 * @param nrow Number of rows in the matrix
 * @param ncol Number of columns in the matrix
 * @param mat_name Name of the matrix
 */
void showMat(MYTYPE* mat, int nrow, int ncol, const char mat_name[]){
    printf("Matrice %s is %d x %d\n", mat_name, nrow, ncol);
    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncol; j++){
            printf("%f\t", mat[i*ncol+j]);
        }
        printf("\n");
    }
}
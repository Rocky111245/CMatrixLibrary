#include "library.h"
#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"


typedef struct
{
    float* data;
    int row;
    int column;
}
Matrix;


Matrix Matrix_Create_Zero (int rows, int columns);
Matrix Matrix_Create (int rows, int columns);
void Matrix_Free(Matrix* matrix) ;
Matrix Matrix_Multiply( Matrix firstMatrix, Matrix secondMatrix);
void Matrix_Display(Matrix matrix);
Matrix *Matrix_Allocate(int rows, int columns);
int Matrix_Index_Finder( int maxColumns, int desiredRow,int desiredColumn);
float* Array_Scalar_Multiply(int end, float multiplier, float *array);
float* Array_Add(int size,float *firstArray, float *secondArray);


int main(){
    Matrix first= Matrix_Create(4,4);
    Matrix second= Matrix_Create(4,4);

    Matrix third=Matrix_Multiply(first,second);
    Matrix_Display(third);
    Matrix_Free(&first);
    Matrix_Free(&second);
    Matrix_Free(&third);




}

Matrix Matrix_Create (int rows, int columns){
    Matrix M;
    M.row=rows;
    M.column=columns;
    M.data=(float*) malloc(rows*columns*sizeof(float));
    int index;
    //This creates a contagious heap of rows||columns||pointer to data->data[0]
    if (M.data == NULL) {
        exit(1);
    }
    for (int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            index= Matrix_Index_Finder(columns,i,j);
            scanf("%f",&M.data[index]);
        }
    }
    return M;
}


Matrix Matrix_Create_Zero (int rows, int columns){
    Matrix M;
    M.row=rows;
    M.column=columns;
    M.data=(float*) calloc(rows*columns,sizeof(float));
    //This creates a contagious heap of rows||columns||pointer to data->data[0]
    if (M.data == NULL) {
        exit(1);
    }
    return M;
}


void Matrix_Free(Matrix* matrix) {
    // Check if the data pointer is not NULL before freeing
    if (matrix->data != NULL) {
        free(matrix->data); // Free the dynamically allocated matrix data
        matrix->data = NULL; // Set the data pointer to NULL to avoid dangling pointers
    }
    // No need to free the matrix itself when it's allocated on the stack or as a static/global variable
}


void Matrix_Display(Matrix matrix) {
    int rows=matrix.row;
    int columns=matrix.column;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%f ", matrix.data[i * columns + j]);
        }
        printf("\n");
    }
}


Matrix Matrix_Multiply( Matrix firstMatrix, Matrix secondMatrix){
    if(firstMatrix.column!=secondMatrix.row){
        printf("It is not mathematically possible to multiply two matrices where the number of column in the first matrix does not equal the number of rows in the second matrix");
        exit(1);
    }
    int index;
    int thirdMatrix_index=0;
    //we have to calculate the size of the third matrix.
    int maxRow=firstMatrix.row;
    int maxColumn=secondMatrix.column;
    int k;
    int n;
    Matrix  Matrix_thirdMatrix= Matrix_Create_Zero(maxRow,maxColumn);
    for(k=0;k<maxRow;k++) {
        n=0;
        float *sum = (float*) calloc(maxColumn,sizeof(float)); // Allocate memory for maxColumn floats
        // Check if memory allocation was successful
        if (sum == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
        }
        for (int i = 0; i < maxColumn; i++) {
            float array[maxColumn];
            for (int m = 0; m < maxColumn; m++, n++) {
                array[m] = secondMatrix.data[n];
            }
            index = Matrix_Index_Finder(maxColumn, k, i);
            float *multipliedArray = Array_Scalar_Multiply(maxColumn, firstMatrix.data[index], array);
            sum=Array_Add(maxColumn, sum, multipliedArray);
            free(multipliedArray);
        }
        for (int m = 0; m < maxColumn; m++,thirdMatrix_index++) {
            Matrix_thirdMatrix.data[thirdMatrix_index]=sum[m];
        }
        free(sum);
    }
    return Matrix_thirdMatrix;

}








//a mathematical way to finding the index
int Matrix_Index_Finder(int maxColumns, int desiredRow, int desiredColumn) {
    return desiredRow * maxColumns + desiredColumn;
}




float* Array_Scalar_Multiply(int end, float multiplier, float *array){
    float *newArray = (float *) malloc(end * sizeof(float)); // Correct allocation size
    for (int i = 0; i < end; i++) {
        newArray[i] = multiplier * array[i];
    }
    return newArray;
}

float* Array_Add(int size, float *firstArray, float *secondArray){
    float *thirdArray = (float *) malloc(size * sizeof(float)); // Correct allocation size
    for (int i = 0; i < size; i++) {
        thirdArray[i] = firstArray[i] + secondArray[i];
    }
    return thirdArray;
}







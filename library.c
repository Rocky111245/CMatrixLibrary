#include "library.h"
#include <stdio.h>


//creates a matrix with user input
Matrix Matrix_User_Input (int rows, int columns){
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


//creates a 0 matrix
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

Matrix MatrixMaker_2DArray( int dataRows, int desiredRows,int desiredColumns,int stride, int data[][dataRows]){
    Matrix M;
    M.row=desiredRows;
    M.column=desiredColumns;
    M.data=(float*) calloc(desiredRows*desiredColumns,sizeof(float));
    int index=0;
    //This creates a contagious heap of rows||columns||pointer to data->data[0]
    if (M.data == NULL) {
        exit(1);
    }
    for (int i=0;i<desiredRows;i++){
        for (int j=0+stride;j<desiredColumns+stride;j++){
            M.data[index]=data[i][j];
            index++;
        }

    }
    return M;
}




//creates a matrix with random number of elements, this matrix can also control the weight scaling
Matrix Matrix_Create_Random(int rows, int columns, int scale) {
    Matrix M;
    M.row = rows;
    M.column = columns;
    M.data = (float*) malloc(rows * columns * sizeof(float));
    if (M.data == NULL) {
        exit(1); // Exit if memory allocation fails
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int index = Matrix_Index_Finder(columns, i, j);
            // Generate a random float between 1 and 10
            M.data[index] = 1 + (rand() / (RAND_MAX / (scale - 1.0f)));
        }
    }
    return M;
}

void Matrix_Transpose(Matrix *final,Matrix original){
    int originalMatrixIndex=0;
    int finalMatrixIndex=0;
    int i;
    int j;
    for (j=0;j<original.row;j++) {
        for (i = 0; i < original.column; i++) {
            originalMatrixIndex = Matrix_Index_Finder(original.column, j, i);
            finalMatrixIndex = Matrix_Index_Finder(final->column, i, j);
            final->data[finalMatrixIndex]=original.data[originalMatrixIndex];
        }
    }
}

//frees memory
void Matrix_Free(Matrix* matrix) {
    // Check if the data pointer is not NULL before freeing
    if (matrix->data != NULL) {
        free(matrix->data); // Free the dynamically allocated matrix data
        matrix->data = NULL; // Set the data pointer to NULL to avoid dangling pointers
    }
    // No need to free the matrix itself when it's allocated on the stack or as a static/global variable
}


//This function displays a matrix
void Matrix_Display(Matrix matrix) {
    int rows=matrix.row;
    int columns=matrix.column;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("|%f ", matrix.data[i * columns + j]);
        }
        printf("\n");
    }
}


void Matrix_Add(Matrix *result, Matrix matrix1, Matrix matrix2) {
    // Ensure both matrices have the same dimensions
    if (matrix1.row != matrix2.row || matrix1.column != matrix2.column) {
        printf("Error: Matrices dimensions do not match.\n");
        exit(1);
    }

    // Assuming 'result' matrix is pre-allocated and has the same dimensions as 'matrix1' and 'matrix2'
    for (int i = 0; i < matrix1.row; i++) {
        for (int j = 0; j < matrix1.column; j++) {
            int index = Matrix_Index_Finder(matrix1.column, i, j);
            result->data[index] = matrix1.data[index] + matrix2.data[index];
        }
    }
}


//Multiplies two matrices, returns pointer to third matrix. A unique way to multiple matrices
void Matrix_Multiply(Matrix *finalMatrix, Matrix firstMatrix, Matrix secondMatrix){
    int indexFirstMatrix;
    int indexSecondMatrix;
    int indexFinalMatrix=0;
    float sum=0;
    int i;
    int j;
    int k;
    if(firstMatrix.column!=secondMatrix.row){
        printf("It is not mathematically possible to multiply two matrices where the number of column in the first matrix does not equal the number of rows in the second matrix");
        exit(1);
    }
    for (k=0;k<firstMatrix.row;k++){
        for (j=0;j<secondMatrix.column;j++){
            sum=0;
            for ( i=0;i<firstMatrix.column;i++){
                indexFirstMatrix= Matrix_Index_Finder(firstMatrix.column,k,i);
                indexSecondMatrix= Matrix_Index_Finder(secondMatrix.column,i,j);
                sum=sum+(firstMatrix.data[indexFirstMatrix]*secondMatrix.data[indexSecondMatrix]);
            }
            finalMatrix->data[indexFinalMatrix++]=sum;
        }
    }
}


//a mathematical way to finding the index
int Matrix_Index_Finder(int maxColumns, int desiredRow, int desiredColumn) {
    return desiredRow * maxColumns + desiredColumn;
}








//multiplies a Matrix with a scalar
float* Array_Scalar_Multiply(int length, float multiplier, float *array){
    float *newArray = (float *) malloc(length * sizeof(float)); // Correct allocation size
    for (int i = 0; i < length; i++) {
        newArray[i] = multiplier * array[i];
    }
    return newArray;
}

//adds two arrays with sizes that respect each other
float* Array_Add(int size, float *firstArray, float *secondArray){
    float *thirdArray = (float *) malloc(size * sizeof(float)); // Correct allocation size
    for (int i = 0; i < size; i++) {
        thirdArray[i] = firstArray[i] + secondArray[i];
    }
    return thirdArray;
}

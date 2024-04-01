#include "library.h"
#include <stdio.h>

//Custom Linear Algebra Matrices Library

//Creates a matrix with user input type struct
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


//Creates a Zero Matrix
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

//Chops down a 2d array to struct format. Useful for separating training and test datasets.
Matrix Matrix_Maker_2DArray(int maxColumns, int desiredRows, int desiredColumns, int stride, const float *data){
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
            int dataIndex= Matrix_Index_Finder(maxColumns,i,j);
            M.data[index]=data[dataIndex];
            index++;
        }
    }
    return M;
}


//converts a 2d array to struct
Matrix Matrix_to_Struct(int maxColumn,int size, const float *data){
    Matrix M;
    M.row=size;
    M.column=maxColumn;
    M.data=(float*) calloc(M.row*M.column,sizeof(float));
    int index=0;
    //This creates a contagious heap of rows||columns||pointer to data->data[0]
    if (M.data == NULL) {
        exit(1);
    }
    for (int i=0;i<M.row;i++){
        for (int j=0;j<M.column;j++){
            int dataIndex= Matrix_Index_Finder(maxColumn,i,j);
            M.data[index]=data[dataIndex];
            index++;
        }

    }
    return M;
}


//Creates a matrix with a random number of elements, this matrix can also control the weight scaling
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

//Transposes the matrix
void Matrix_Transpose(Matrix *final,Matrix original){
    int originalMatrixIndex;
    int finalMatrixIndex;
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

//Frees memory
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
    printf("\n");
}

//Adds two struct matrices
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

//Subtracts two struct matrices
void Matrix_Subtract(Matrix *result, Matrix matrix1, Matrix matrix2) {
    // Ensure both matrices have the same dimensions
    if (matrix1.row != matrix2.row || matrix1.column != matrix2.column) {
        printf("Error: Matrices dimensions do not match.\n");
        exit(1);
    }

    // Assuming 'result' matrix is pre-allocated and has the same dimensions as 'matrix1' and 'matrix2'
    for (int i = 0; i < matrix1.row; i++) {
        for (int j = 0; j < matrix1.column; j++) {
            int index = Matrix_Index_Finder(matrix1.column, i, j);
            result->data[index] = matrix1.data[index] - matrix2.data[index];
        }
    }
}


//Multiplies two matrices, returns pointer to third matrix.
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


//A mathematical way of finding the index
int Matrix_Index_Finder(int maxColumns, int desiredRow, int desiredColumn) {
    return desiredRow * maxColumns + desiredColumn;
}



//Multiplies a Matrix with a scalar
float* Array_Scalar_Multiply(int length, float multiplier, const float *array){
    float *newArray = (float *) malloc(length * sizeof(float)); // Correct allocation size
    for (int i = 0; i < length; i++) {
        newArray[i] = multiplier * array[i];
    }
    return newArray;
}

//Adds two arrays with sizes that respect each other
float* Array_Add(int size, const float *firstArray, const float *secondArray){
    float *thirdArray = (float *) malloc(size * sizeof(float)); // Correct allocation size
    for (int i = 0; i < size; i++) {
        thirdArray[i] = firstArray[i] + secondArray[i];
    }
    return thirdArray;
}

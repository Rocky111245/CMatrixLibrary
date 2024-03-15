#include "library.h"
#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include <time.h>


typedef struct
{
    float* data;
    int row;
    int column;
}
Matrix;


Matrix Matrix_Create_Zero (int rows, int columns);
Matrix Matrix_Create_Input (int rows, int columns);
void Matrix_Free(Matrix* matrix) ;
Matrix Matrix_Multiply( Matrix firstMatrix, Matrix secondMatrix);
void Matrix_Display(Matrix matrix);
Matrix *Matrix_Allocate(int rows, int columns);
int Matrix_Index_Finder( int maxColumns, int desiredRow,int desiredColumn);
float* Array_Scalar_Multiply(int length, float multiplier, float *array);
float* Array_Add(int size,float *firstArray, float *secondArray);
Matrix Matrix_Create_Random(int rows, int columns, int scale);


int main(){
    // Seed the random number generator
    srand((unsigned) time(NULL));
//    Matrix x=Matrix_Create_Random(3,3,10);
//    Matrix y=Matrix_Create_Random(3,3,100);
//    Matrix_Display(x);
    Matrix x= Matrix_Create_Input(2,3);
    Matrix y= Matrix_Create_Input(3,3);
    Matrix z= Matrix_Multiply(x,y);
    printf("\n");
    Matrix_Display(z);
}


//creates a matrix with user input
Matrix Matrix_Create_Input (int rows, int columns){
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
            printf("%f ", matrix.data[i * columns + j]);
        }
        printf("\n");
    }
}


//Multiplies two matrices, returns pointer to third matrix. A unique way to multiple matrices
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
    Matrix Matrix_thirdMatrix= Matrix_Create_Zero(maxRow,maxColumn);
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







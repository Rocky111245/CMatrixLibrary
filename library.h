#ifndef CMATRIXLIBRARY_LIBRARY_H
#define CMATRIXLIBRARY_LIBRARY_H


#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include <time.h>


typedef struct
{
    float* data;
    int row;
    int column;
}Matrix;


Matrix Matrix_Create_Zero (int rows, int columns);
Matrix Matrix_User_Input (int rows, int columns);
Matrix MatrixMaker_2DArray( int dataRows, int desiredRows,int desiredColumns,int stride,int data[][dataRows]);
void Matrix_Transpose(Matrix *final,Matrix original);
void Matrix_Free(Matrix* matrix) ;
void Matrix_Add(Matrix *result, Matrix matrix1, Matrix matrix2);
void Matrix_Multiply(Matrix *finalMatrix, Matrix firstMatrix, Matrix secondMatrix);
void Matrix_Display(Matrix matrix);
Matrix *Matrix_Allocate(int rows, int columns);
int Matrix_Index_Finder( int maxColumns, int desiredRow,int desiredColumn);
float* Array_Scalar_Multiply(int length, float multiplier, float *array);
float* Array_Add(int size,float *firstArray, float *secondArray);
Matrix Matrix_Create_Random(int rows, int columns, int scale);

#endif //CMATRIXLIBRARY_LIBRARY_H

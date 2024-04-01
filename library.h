#ifndef CMATRIXLIBRARY_LIBRARY_H
#define CMATRIXLIBRARY_LIBRARY_H

#ifdef __cplusplus
extern "C" {
#endif


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
Matrix Matrix_Maker_2DArray(int maxColumns, int desiredRows, int desiredColumns, int stride,  const float *data);
void Matrix_Transpose(Matrix *final,Matrix original);
void Matrix_Free(Matrix* matrix) ;
void Matrix_Add(Matrix *result, Matrix matrix1, Matrix matrix2);
void Matrix_Subtract(Matrix *result, Matrix matrix1, Matrix matrix2);
void Matrix_Multiply(Matrix *finalMatrix, Matrix firstMatrix, Matrix secondMatrix);
void Matrix_Display(Matrix matrix);
Matrix Matrix_to_Struct(int maxColumn,int size, const float *data);
Matrix *Matrix_Allocate(int rows, int columns);
int Matrix_Index_Finder( int maxColumns, int desiredRow,int desiredColumn);
float* Array_Scalar_Multiply(int length, float multiplier, const float *array);
float* Array_Add(int size,const float *firstArray, const float *secondArray);
Matrix Matrix_Create_Random(int rows, int columns, int scale);

#ifdef __cplusplus
} // Closing extern "C"
#endif

#endif // CMATRIXLIBRARY_LIBRARY_H
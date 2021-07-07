#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define M_PI 3.14159265358979323846

void matrixScale(float* , float , float, float );
void matrixFrustum(float* , float , float , float , float , float , float );
void matrixOrtho(float*, float , float , float , float , float , float );
void matrixPerspective(float* , float , float , float , float);
void matrixTranslate(float* , float , float , float );
void matrixRotateX(float*, float);
void matrixRotateY(float*, float);
void matrixRotateZ(float*, float);


void loadIdentity(float* );
void multiplyMatrix(float* , float* , float* );

float degToRad(float);
void printMatrix(float*);
void copyMatrix_fd(float*, double*);
#endif // MATRIX_H_INCLUDED

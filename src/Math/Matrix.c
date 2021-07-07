#include "Matrix.h"


void matrixScale(float* matrix, float x, float y, float z)
{
    float tempMatrix[16];
    loadIdentity(tempMatrix);
    tempMatrix[0] = x;
    tempMatrix[5] = y;
    tempMatrix[10] = z;
    multiplyMatrix(matrix, tempMatrix, matrix);
}

void matrixFrustum(float* matrix, float left, float right, float bottom, float top, float zNear, float zFar)
{
    float temp, xDistance, yDistance, zDistance;
    temp = 2.0 *zNear;
    xDistance = right - left;
    yDistance = top - bottom;
    zDistance = zFar - zNear;
    loadIdentity(matrix);
    matrix[0] = temp / xDistance;
    matrix[5] = temp / yDistance;
    matrix[8] = (right + left) / xDistance;
    matrix[9] = (top + bottom) / yDistance;
    matrix[10] = (-zFar - zNear) / zDistance;
    matrix[11] = -1.0f;
    matrix[14] = (-temp * zFar) / zDistance;
    matrix[15] = 0.0f;
}

void matrixOrtho(float* matrix, float bottom, float top, float left, float right, float near, float far)
{
    loadIdentity(matrix);
    matrix[0] = 2 / (right - left);
    matrix[5] = 2 / (top - bottom);
    matrix[10] = -2 / (far - near);
    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[14] = -(far + near) / (far - near);
    matrix[15] = 1;
}

void matrixPerspective(float* matrix, float fieldOfView, float aspectRatio, float zNear, float zFar)
{
    float ymax, xmax;
    ymax = zNear * tanf(fieldOfView * M_PI / 360.0);
    xmax = ymax * aspectRatio;
    matrixFrustum(matrix, -xmax, xmax, -ymax, ymax, zNear, zFar);
}

void matrixTranslate(float* matrix, float x, float y, float z)
{
    float tempMatrix[16];
    loadIdentity(tempMatrix);
    tempMatrix[12] = x;
    tempMatrix[13] = y;
    tempMatrix[14] = z;
    multiplyMatrix(matrix, tempMatrix, matrix);
}

void loadIdentity(float* matrix)
{
    if(matrix == NULL)
    {
        return;
    }
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;
    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;
    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

void multiplyMatrix(float* destination, float* operand1, float* operand2)
{
    float theResult[16];
    int i,j = 0;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            theResult[4 * i + j] = operand1[j] * operand2[4 * i] + operand1[4 + j] * operand2[4 * i + 1] +
                operand1[8 + j] * operand2[4 * i + 2] + operand1[12 + j] * operand2[4 * i + 3];
        }
    }
    for(int i = 0; i < 16; i++)
    {
        destination[i] = theResult[i];
    }
}


void matrixRotateX(float* matrix, float angle)
{
    float tempMatrix[16];
    loadIdentity(tempMatrix);
    tempMatrix[5] = cos(degToRad(angle));
    tempMatrix[9] = -sin(degToRad(angle));
    tempMatrix[6] = sin(degToRad(angle));
    tempMatrix[10] = cos(degToRad(angle));
    multiplyMatrix(matrix, tempMatrix, matrix);
}
void matrixRotateY(float *matrix, float angle)
{
    float tempMatrix[16];
    loadIdentity(tempMatrix);
    tempMatrix[0] = cos(degToRad(angle));
    tempMatrix[8] = sin(degToRad(angle));
    tempMatrix[2] = -sin(degToRad(angle));
    tempMatrix[10] = cos(degToRad(angle));
    multiplyMatrix(matrix, tempMatrix, matrix);
}
void matrixRotateZ(float *matrix, float angle)
{
    float tempMatrix[16];
    loadIdentity(tempMatrix);
    tempMatrix[0] = cos(degToRad(angle));
    tempMatrix[4] = -sin(degToRad(angle));
    tempMatrix[1] = sin(degToRad(angle));
    tempMatrix[5] = cos(degToRad(angle));
    multiplyMatrix(matrix, tempMatrix, matrix);
}

float degToRad(float degrees)
{
    return M_PI * degrees / 180.0f;
}

void printMatrix_d(double* Matrix)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("%f\t", Matrix[i * 4 + j]);
        }
    printf("\n");
    }
}

void printMatrix_f(float* Matrix)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            printf("%f\t", Matrix[i * 4 + j]);
        }
    printf("\n");
    }
}

void copyMatrix_fd(float* src, double* dest)
{
    for (int i = 0; i < 16; i++)
    {
        dest[i] = (double)src[i];
    }
}

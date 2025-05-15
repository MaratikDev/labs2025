#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "Point3D.h"
#define MATRIX_SIZE 4


class TransformMatrix
{
public:
    TransformMatrix();
    friend TransformMatrix operator *(const TransformMatrix& firstMat, const TransformMatrix& secondMat);
    point3D transformPoint(point3D point);
    float matr[MATRIX_SIZE][MATRIX_SIZE];
};

#endif // TRANSFORMMATRIX_H

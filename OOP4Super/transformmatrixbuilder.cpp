#include "TransformMatrixBuilder.h"
#include <cmath>

TransformMatrix TransformMatrixBuilder::createMoveMatrix(float x, float y, float z) {
    TransformMatrix matrix;
    matrix.matr[0][3] = x;
    matrix.matr[1][3] = y;
    matrix.matr[2][3] = z;
    return matrix;
}

TransformMatrix TransformMatrixBuilder::createRotationMatrix(float x, float y, float z) {
    TransformMatrix rx, ry, rz ;

    //  X
    rx.matr[1][1] = cos(x); rx.matr[1][2] = -sin(x);
    rx.matr[2][1] = sin(x); rx.matr[2][2] = cos(x);
    rx.matr[0][0] = 1; rx.matr[3][3] = 1;

    //  Y
    ry.matr[0][0] = cos(y); ry.matr[0][2] = sin(y);
    ry.matr[2][0] = -sin(y); ry.matr[2][2] = cos(y);
    ry.matr[1][1] = 1; ry.matr[3][3] = 1;

    //  Z
    rz.matr[0][0] = cos(z); rz.matr[0][1] = -sin(z);
    rz.matr[1][0] = sin(z); rz.matr[1][1] = cos(z);
    rz.matr[2][2] = 1; rz.matr[3][3] = 1;

    return rz * ry * rx;
}

TransformMatrix TransformMatrixBuilder::createScaleMatrix(float x, float y, float z) {
    TransformMatrix matrix;
    matrix.matr[0][0] = x;
    matrix.matr[1][1] = y;
    matrix.matr[2][2] = z;
    return matrix;
}

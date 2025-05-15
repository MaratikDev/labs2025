#include "TransformMatrix.h"
#include "qdebug.h"
#include "qlogging.h"
#include <cmath>
TransformMatrix::TransformMatrix(){
    for(int i = 0;i<4;i++){
        for (int j = 0;j<4;j++){
            if(i == j)
                matr[i][j] = 1;
            else{
                matr[i][j] = 0;
            }
        }
    }
}

point3D TransformMatrix::transformPoint(point3D point) {
    point3D result;
    result.x = matr[0][0] * point.x + matr[0][1] * point.y + matr[0][2] * point.z + matr[0][3];
    result.y = matr[1][0] * point.x + matr[1][1] * point.y + matr[1][2] * point.z + matr[1][3];
    result.z = matr[2][0] * point.x + matr[2][1] * point.y + matr[2][2] * point.z + matr[2][3];
    return result;
}

TransformMatrix operator*(const TransformMatrix& firstMat, const  TransformMatrix& secondMat) {
    TransformMatrix result;
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            result.matr[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                result.matr[i][j] += firstMat.matr[i][k] * secondMat.matr[k][j];
            }
        }
    }
    return result;
}

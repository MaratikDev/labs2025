#ifndef TRANSFORMMATRIXBUILDER_H
#define TRANSFORMMATRIXBUILDER_H

#include "transformmatrix.h"

class TransformMatrixBuilder
{
public:
    TransformMatrixBuilder();
    static TransformMatrix createRotationMatrix(float x, float y, float z);
    static TransformMatrix createMoveMatrix(float x, float y, float z);
    static TransformMatrix createScaleMatrix(float x, float y, float z);
};

#endif // TRANSFORMMATRIXBUILDER_H

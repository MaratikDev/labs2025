#include "facade.h"
#include "filereader.h"
#include "qtscenedrawer.h"


Facade::Facade(SceneDrawerBase* drawer) :
    fileReader(new FileReader()),
    sceneDrawer(drawer) {transformMatrix = TransformMatrix();}

FacadeOperationResult Facade::drawScene() {
    if (!sceneDrawer) return FacadeOperationResult(false, "Scene drawer not initialized");
    scene.transformFigures(transformMatrix);
    transformMatrix = TransformMatrix();
    sceneDrawer->drawScene(scene);
    return FacadeOperationResult(true, "");
}

FacadeOperationResult Facade::loadScene(char* path, NormalizationParameters params) {
    if (!fileReader) return FacadeOperationResult(false, "File reader not initialized");
    scene = fileReader->readScene(path, params);
    transformMatrix = TransformMatrix();
    return FacadeOperationResult(true, "");
}

FacadeOperationResult Facade::moveScene(float x, float y, float z) {
    auto matrix = TransformMatrixBuilder::createMoveMatrix(x, y, z);

    transformMatrix = matrix * transformMatrix;
    return FacadeOperationResult(true, "");
}

FacadeOperationResult Facade::rotateScene(float x, float y, float z) {
    auto matrix = TransformMatrixBuilder::createRotationMatrix(x, y, z);

    transformMatrix = matrix * transformMatrix;
    return FacadeOperationResult(true,"");
}

FacadeOperationResult Facade::scaleScene(float x, float y, float z) {
    auto matrix = TransformMatrixBuilder::createScaleMatrix(x, y, z);

    transformMatrix = matrix * transformMatrix;
    return FacadeOperationResult(true,"");
}

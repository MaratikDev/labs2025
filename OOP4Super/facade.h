#ifndef FACADE_H
#define FACADE_H

#include "NormalizationParameters.h"
#include "basefilereader.h"
#include "facadeoperationresult.h"
#include "scenedrawerbase.h"
#include "transformmatrixbuilder.h"
#include "qtscenedrawer.h"
#include "scenedrawerbase.h"
#include "scene.h"
class Facade
{
public:
    Facade(SceneDrawerBase* drawer);
    FacadeOperationResult drawScene();
    FacadeOperationResult loadScene(char* path, NormalizationParameters params);
    FacadeOperationResult moveScene(float x, float y, float z);
    FacadeOperationResult rotateScene(float x, float y, float z);
    FacadeOperationResult scaleScene(float x, float y, float z);
private:
    BaseFileReader* fileReader;
    SceneDrawerBase* sceneDrawer;
    Scene scene;
    TransformMatrix transformMatrix;
};

#endif // FACADE_H

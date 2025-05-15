#ifndef BASEFILEREADER_H
#define BASEFILEREADER_H

#include "NormalizationParameters.h"
#include "scene.h"

class BaseFileReader
{
public:
    virtual Scene readScene(char* path, NormalizationParameters params) = 0;
};

#endif // BASEFILEREADER_H

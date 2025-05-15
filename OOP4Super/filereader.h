#ifndef FILEREADER_H
#define FILEREADER_H
#include "basefilereader.h"
class FileReader : public BaseFileReader
{
public:
    Scene readScene(char* path, NormalizationParameters params) override;
};

#endif // FILEREADER_H

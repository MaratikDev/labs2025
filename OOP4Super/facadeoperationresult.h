#ifndef FACADEOPERATIONRESULT_H
#define FACADEOPERATIONRESULT_H

#include <string>
class FacadeOperationResult
{
public:
    FacadeOperationResult(bool success, const std::string& error);
    bool isSuccess();
    std::string getErrorMessage();
private:
    std::string errorMessage;
    bool _isSuccess;

};

#endif // FACADEOPERATIONRESULT_H

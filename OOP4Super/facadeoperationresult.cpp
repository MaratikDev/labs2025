#include "facadeoperationresult.h"

FacadeOperationResult::FacadeOperationResult(bool success, const std::string& error) :
    errorMessage(error), _isSuccess(success) {}

bool FacadeOperationResult::isSuccess() { return _isSuccess; }
std::string FacadeOperationResult::getErrorMessage() { return errorMessage; }

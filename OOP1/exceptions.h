#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
#include <string>


class ShapeException : public std::exception {
public:
    explicit ShapeException(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class InvalidChoiceException : public ShapeException {
public:
    explicit InvalidChoiceException(const std::string& message) : ShapeException(message) {}
};


class InvalidParameterException : public ShapeException {
public:
    explicit InvalidParameterException(const std::string& message) : ShapeException(message) {}
};
#endif // EXCEPTIONS_H

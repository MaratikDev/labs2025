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

class InvalidTypeException : public ShapeException {
public:
    explicit InvalidTypeException(const std::string& message) : ShapeException(message) {}
};


class OutOfIndexException : public ShapeException {
public:
    explicit OutOfIndexException(const std::string& message) : ShapeException(message) {}
};

class DevideByZeroException : public ShapeException {
public:
    explicit DevideByZeroException(const std::string& message) : ShapeException(message) {}
};
#endif // EXCEPTIONS_H

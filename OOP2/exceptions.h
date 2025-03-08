#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
#include <string>


class InvalidTypeException : public std::exception {
public:
    explicit InvalidTypeException(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class OutOfIndexException : public std::exception {
public:
    explicit OutOfIndexException(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class DevideByZeroException : public std::exception {
public:
    explicit DevideByZeroException(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class FileException : public std::exception {
public:
    explicit FileException(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};


class EmptyException : public std::exception {
public:
    explicit EmptyException(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

#endif // EXCEPTIONS_H

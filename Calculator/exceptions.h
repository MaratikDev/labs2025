#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
#include <string>

class InfinityProblem : public std::exception {
public:
    explicit InfinityProblem(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class NegativeSqrt : public std::exception {
public:
    explicit NegativeSqrt(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class ExpressionError : public std::exception {
public:
    explicit ExpressionError(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};



#endif // EXCEPTIONS_H

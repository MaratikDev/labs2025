#ifndef DEIKSTRA_H
#define DEIKSTRA_H

#include <string>
#include <vector>
#include <stack>
#include <map>
#include <memory>
#include "commands.h"
#include "factoryCommand.h"

class Deikstra {
public:
    Deikstra();
    double evaluate(const std::string& expression) const;

private:
    std::vector<std::string> tokenize(const std::string& expression) const;
    bool isNumber(const std::string& token) const;
    bool isOperator(const std::string& token) const;
    bool isFunction(const std::string& token) const;
    bool isLeftParenthesis(const std::string& token) const;
    bool isRightParenthesis(const std::string& token) const;
    std::vector<std::string> postfix(const std::string& expression) const;
    double calculate(std::vector<std::string> postfix) const;

    std::map<std::string, CommandFactory::CommandCreator> operations;
    CommandFactory factory;
};

#endif // DEIKSTRA_H

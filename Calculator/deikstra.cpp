#include "deikstra.h"
#include "factoryCommand.h"
#include "qdebug.h"
#include "qlogging.h"
#include <sstream>
#include <cctype>
#include <stdexcept>

Deikstra::Deikstra() {
    // Инициализация операций с указателями на методы CommandFactory
    operations["+"] = &CommandFactory::createPlus;
    operations["-"] = &CommandFactory::createMinus;
    operations["*"] = &CommandFactory::createMultiply;
    operations["/"] = &CommandFactory::createDivide;

    operations["sqrt"] = &CommandFactory::createSqrt;
    operations["sin"] = &CommandFactory::createSin;
    operations["cos"] = &CommandFactory::createCos;
    operations["tan"] = &CommandFactory::createTan;
    operations["cot"] = &CommandFactory::createCot;
    operations["inv"] = &CommandFactory::createInv;
}

std::vector<std::string> Deikstra::tokenize(const std::string& expression) const {
    qDebug() << expression;
    std::vector<std::string> tokens;
    std::string currentToken;
    bool prevWasOperatorOrParen = true;

    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];

        if ((c == '-') && (prevWasOperatorOrParen || (i == 0) || (i > 0 && expression[i-1] == '('))) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            currentToken += c;
        }
        else if (isOperator(std::string(1, c)) || c == '(' || c == ')') {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back(std::string(1, c));
            prevWasOperatorOrParen = (c != ')');
        }
        else {
            currentToken += c;
            prevWasOperatorOrParen = false;
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

bool Deikstra::isNumber(const std::string& token) const {
    if (token.empty()) return false;

    size_t start = 0;
    if (token[0] == '-') {
        if (token.size() == 1) return false;
        start = 1;
    }

    bool hasDot = false;
    for (size_t i = start; i < token.size(); ++i) {
        if (token[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        }
        else if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

bool Deikstra::isOperator(const std::string& token) const {
    return operations.count(token) && !(factory.*operations.at(token))(0, 0)->isFunction();
}

bool Deikstra::isFunction(const std::string& token) const {
    return operations.count(token) && (factory.*operations.at(token))(0, 0)->isFunction();
}

bool Deikstra::isLeftParenthesis(const std::string& token) const {
    return token == "(";
}

bool Deikstra::isRightParenthesis(const std::string& token) const {
    return token == ")";
}

double Deikstra::evaluate(const std::string& expression) const {
    return calculate(postfix(expression));
}

std::vector<std::string> Deikstra::postfix(const std::string& expression) const {
    std::vector<std::string> tokens = tokenize(expression);
    std::stack<std::string> operatorStack;
    std::vector<std::string> output;

    for (const auto& token : tokens) {
        qDebug() << token;

        if (isNumber(token)) {
            output.push_back(token);
        }
        else if (isFunction(token)) {
            operatorStack.push(token);
        }
        else if (isOperator(token)) {
            while (!operatorStack.empty()) {
                const std::string& top = operatorStack.top();

                if (isOperator(top)) {
                    Command* cmd1 = (factory.*operations.at(token))(0, 0);
                    Command* cmd2 = (factory.*operations.at(top))(0, 0);

                    if (cmd1->precedence() <= cmd2->precedence()) {
                        output.push_back(top);
                        operatorStack.pop();
                        delete cmd1;
                        delete cmd2;
                        continue;
                    }
                    delete cmd1;
                    delete cmd2;
                }
                else if (isFunction(top)) {
                    output.push_back(top);
                    operatorStack.pop();
                    continue;
                }
                break;
            }

            operatorStack.push(token);
        }
        else if (isLeftParenthesis(token)) {
            operatorStack.push(token);
        }
        else if (isRightParenthesis(token)) {
            while (!operatorStack.empty() && !isLeftParenthesis(operatorStack.top())) {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }

            if (operatorStack.empty()) {
                throw std::runtime_error("Mismatched parentheses");
            }

            operatorStack.pop(); // Удаляем "("

            if (!operatorStack.empty() && isFunction(operatorStack.top())) {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }
        }
    }

    while (!operatorStack.empty()) {
        if (isLeftParenthesis(operatorStack.top())) {
            throw std::runtime_error("Mismatched parentheses");
        }
        output.push_back(operatorStack.top());
        operatorStack.pop();
    }

    return output;
}

double Deikstra::calculate(std::vector<std::string> postfix) const {
    std::stack<double> evalStack;
    qDebug() << "postfix:";

    for (const auto& token : postfix) {
        qDebug() << token;

        if (isNumber(token)) {
            evalStack.push(std::stod(token));
        }
        else if (operations.count(token)) {
            auto creator = operations.at(token);

            if (isFunction(token)) {
                // Унарные операции
                if (evalStack.empty()) throw ExpressionError("Not enough operands");
                double a = evalStack.top();
                evalStack.pop();

                Command* cmd = (factory.*creator)(a, 0);
                double result = cmd->execute();
                delete cmd;
                evalStack.push(result);
            }
            else {
                // Бинарные операции
                if (evalStack.size() < 2) throw ExpressionError("Not enough operands");
                double b = evalStack.top(); evalStack.pop();
                double a = evalStack.top(); evalStack.pop();

                Command* cmd = (factory.*creator)(a, b);
                double result = cmd->execute();
                delete cmd;
                evalStack.push(result);
            }
        }
    }

    if (evalStack.size() != 1) {
        throw ExpressionError("Invalid expression");
    }

    return evalStack.top();
}

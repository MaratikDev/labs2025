#include "deikstra.h"
#include "funcfactory.h"
#include "operationfactory.h"
#include "qdebug.h"
#include "qlogging.h"
#include <cctype>
#include <stdexcept>

Deikstra::Deikstra() {
    operations["+"] = &OperationFactory::createPlus;
    operations["-"] = &OperationFactory::createMinus;
    operations["*"] = &OperationFactory::createMultiply;
    operations["/"] = &OperationFactory::createDivide;

    functions["sqrt"] = &FuncFactory::createSqrt;
    functions["sin"] = &FuncFactory::createSin;
    functions["cos"] = &FuncFactory::createCos;
    functions["tan"] = &FuncFactory::createTan;
    functions["cot"] = &FuncFactory::createCot;
    functions["inv"] = &FuncFactory::createInv;
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
    if (token.empty())
        return false;

    size_t start = 0;
    if (token[0] == '-') {
        if (token.size() == 1)
            return false;
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
    return operations.count(token);
}

bool Deikstra::isFunction(const std::string& token) const {
    return functions.count(token);
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
                    Command* cmd1 = (opFactory.*operations.at(token))(0, 0);
                    Command* cmd2 = (opFactory.*operations.at(top))(0, 0);

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
                throw ExpressionError("Mismatched parentheses");
            }

            operatorStack.pop();

            if (!operatorStack.empty() && isFunction(operatorStack.top())) {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }
        }
    }

    while (!operatorStack.empty()) {
        if (isLeftParenthesis(operatorStack.top())) {
            throw ExpressionError("Mismatched parentheses");
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
            // Бинарные операции
            if (evalStack.size() < 2)
                throw ExpressionError("Not enough operands");
            double b = evalStack.top(); evalStack.pop();
            double a = evalStack.top(); evalStack.pop();

            Command* cmd = (opFactory.*operations.at(token))(a, b);
            double result = cmd->execute();
            delete cmd;
            evalStack.push(result);
        }
        else if (functions.count(token)) {
            // Унарные операции
            if (evalStack.empty())
                throw ExpressionError("Not enough operands");
            double a = evalStack.top(); evalStack.pop();

            Command* cmd = (funcFactory.*functions.at(token))(a);
            double result = cmd->execute();
            delete cmd;
            evalStack.push(result);
        }
    }

    if (evalStack.size() != 1) {
        throw ExpressionError("Invalid expression");
    }

    return evalStack.top();
}

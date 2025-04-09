#include "deikstra.h"
#include "qdebug.h"
#include "qlogging.h"
#include <sstream>
#include <cctype>
#include <stdexcept>

Deikstra::Deikstra() {
    // Инициализация операций
    operations["+"] = new PlusCommand();
    operations["-"] = new MinusCommand();
    operations["*"] = new MultiplyCommand();
    operations["/"] = new DivideCommand();

    // Инициализация функций
    operations["sqrt"] = new SqrtCommand();
    operations["sin"] = new SinCommand();
    operations["cos"] = new CosCommand();
    operations["tan"] = new TanCommand();
    operations["cot"] = new CotCommand();
}

std::vector<std::string> Deikstra::tokenize(const std::string& expression) const {
    qDebug()<<expression;
    std::vector<std::string> tokens;
    std::string currentToken;
    bool prevWasOperatorOrParen = true;

    for (int i = 0; i < expression.size(); ++i) {
        char c = expression[i];
        // унарный минус
        if ((c == '-') && (prevWasOperatorOrParen || (i == 0) ||(i > 0 && expression[i-1] == '('))) {
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
        else{
        // Числа и слова функций(типа tan sin)
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

    int start = 0;
    if (token[0] == '-') {
        if (token.size() == 1)
            return false;
        start = 1;
    }

    bool hasDot = false;
    for (int i = start; i < token.size(); ++i) {
        if (token[i] == '.') {
            if (hasDot)
                return false;
            hasDot = true;
        }
        else if (!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

bool Deikstra::isOperator(const std::string& token) const {
    return operations.count(token) && !operations.at(token)->isFunction();
}

bool Deikstra::isFunction(const std::string& token) const {
    return operations.count(token) && operations.at(token)->isFunction();
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

std::vector<std::string> Deikstra::postfix(const std::string& expression) const{
    std::vector<std::string> tokens = tokenize(expression);
    std::stack<std::string> operatorStack;
    std::vector<std::string> output;
    for (const auto& token : tokens) {
        qDebug()<< token;
        if (isNumber(token)) {
            output.push_back(token);
        }
        else if (isFunction(token)) {
            operatorStack.push(token);
        }
        else if (isOperator(token)) {
            const Command* op1 = operations.at(token);

            while (!operatorStack.empty()) {
                const std::string& top = operatorStack.top();

                if (isOperator(top)) {
                    const Command* op2 = operations.at(top);

                    if (op1->precedence() <= op2->precedence()) {
                        output.push_back(top);
                        operatorStack.pop();
                        continue;
                    }
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

            operatorStack.pop(); // Удаляем (

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
    qDebug()<<"postfix:";
    for (const auto& token : postfix) {
        qDebug()<<token;
        if (isNumber(token)) {
            evalStack.push(std::stod(token));
        } else if (operations.count(token)) {
            const Command* cmd = operations.at(token);

            if (cmd->isFunction()) {
                if (evalStack.empty()) {
                    throw ExpressionError("Not enough operands");
                }

                double a = evalStack.top();
                evalStack.pop();
                evalStack.push(cmd->execute(a));
            } else {
                if (evalStack.size() < 2) {
                    throw ExpressionError("Not enough operands");
                }

                double b = evalStack.top();
                evalStack.pop();
                double a = evalStack.top();
                evalStack.pop();
                evalStack.push(cmd->execute(a, b));
            }
        }
    }

    if (evalStack.size() != 1) {
        throw ExpressionError("Invalid expression");
    }

    return evalStack.top();
}

Deikstra::~Deikstra() {
    for (auto& op : operations) {
        delete op.second;
    }
}

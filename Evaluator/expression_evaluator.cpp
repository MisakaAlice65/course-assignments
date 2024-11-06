#include "expression_evaluator.h"
#include <cctype>
#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <regex>



std::string transformExpression(const std::string& expression) {
    std::string result;
    std::regex pattern("\\(\\s*-\\s*(\\d+(\\.\\d+)?)\\)");
    std::smatch match;

    // 确保整个表达式只被搜索一次，以避免重复匹配
    std::string::const_iterator searchStart(expression.cbegin());
    std::string::const_iterator searchEnd(expression.cend());
    if (std::regex_search(searchStart, searchEnd, match, pattern)) {
        std::ssub_match sub_match = match[1]; // 匹配到的数字部分
        result = std::string(match.prefix().first, match.prefix().second); // 匹配到的部分之前的内容
        result += "(0-"; // 替换为 (0-
        result += sub_match.str(); // 数字部分
        result += ")"; // 闭合括号
        result += std::string(match.suffix().first, match.suffix().second); // 匹配到的部分之后的内容
    } else {
        result = expression;
    }
    return result;
}
// 将科学计数法转换为普通数字
double convertScientificNotation(const std::string& str) {
    size_t ePos = str.find('e');
    if (ePos == std::string::npos) {
        ePos = str.find('E');
    }

    if (ePos != std::string::npos) {
        double base = std::stod(str.substr(0, ePos));
        int exponent = std::stoi(str.substr(ePos + 1));
        return base * std::pow(10, exponent);
    }

    return std::stod(str);  // 如果没有科学计数法，直接转换为数字
}

// 处理表达式中的科学计数法部分，将其转换为数字
std::string preprocessScientificNotation(std::string expr) {
    std::regex sciRegex(R"(\d+(\.\d+)?[eE][+-]?\d+)");
    std::smatch match;

    // 查找所有科学计数法并进行转换
    while (std::regex_search(expr, match, sciRegex)) {
        std::string sciStr = match.str();
        long double value = convertScientificNotation(sciStr);
        expr.replace(match.position(), match.length(), std::to_string(value));
    }

    return expr;
}



// 获取运算符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 检查是否为运算符
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// 检查字符是否为数字或小数点
bool isDigit(char c) {
    return std::isdigit(c) || c == '.';
}

// 检查表达式是否合法
bool isValidExpression(const std::string& expr) {
    // 检查空字符串
    if (expr.empty()) {
        return false;
    }

    size_t openParenCount = 0;
    size_t closeParenCount = 0;
    bool prevWasOperator = true;  // 允许表达式开始为运算符

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        // 检查非法字符
        if (!std::isdigit(c) && !isOperator(c) && c != '(' && c != ')' && c != '.' && c!=' ') {
            return false;
        }

        // 检查括号平衡
        if (c == '(') openParenCount++;
        if (c == ')') closeParenCount++;
        if (closeParenCount > openParenCount) return false;

        // 检查连续运算符或数字
        if (isOperator(c)) {
            if (prevWasOperator ) return false;  // 只允许负号
            prevWasOperator = true;
        } else {
            prevWasOperator = false;
        }

        // 表达式不能以运算符开头或结尾
        if (i == 0 || i == expr.size() - 1) {
            if (isOperator(c)) return false;
        }

        // 检查小数点使用规则
        if (c == '.') {
            if (i == 0 || !std::isdigit(expr[i - 1])) return false; // 小数点不能出现在开头
            if (i + 1 < expr.size() && !std::isdigit(expr[i + 1])) return false; // 小数点后必须是数字
        }

        // 检查科学计数法的e或E
        if (c == 'e' || c == 'E') {
            // e前面必须是数字，且e后面要么是数字，要么是符号后跟数字
            if (i == 0 || !std::isdigit(expr[i - 1])) return false;  // e前面必须是数字
            if (i + 1 < expr.size()) {
                char nextChar = expr[i + 1];
                if (nextChar == '+' || nextChar == '-') {
                    if (i + 2 < expr.size() && !std::isdigit(expr[i + 2])) {
                        return false;  // 如果符号后没有数字，则不合法
                    }
                } else if (!std::isdigit(nextChar)) {
                    return false;  // e后面必须是数字或+/-符号
                }
            }
        }
    }

    return openParenCount == closeParenCount;
}


// 执行运算
double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw std::runtime_error("ILLEGAL: Division by zero");
            return a / b;
        default: return 0;
    }
}

// 中缀表达式转后缀表达式
std::string infixToPostfix(const std::string& expr) {
    std::stack<char> operators;
    std::stringstream postfix;

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        if (std::isdigit(c) || c == '.' || c == 'e' || c == 'E') {
            // 处理数字（包括浮点数和科学计数法）
            while (i < expr.size() && (std::isdigit(expr[i]) || expr[i] == '.' || expr[i] == 'e' || expr[i] == 'E')) {
                postfix << expr[i++];
            }
            --i; // 调整 i 以便下一次处理
            postfix << " ";
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix << operators.top() << " ";
                operators.pop();
            }
            operators.pop(); // 弹出 '('
        } else if (isOperator(c)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                postfix << operators.top() << " ";
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix << operators.top() << " ";
        operators.pop();
    }

    return postfix.str();
}


// 后缀表达式求值
double evaluatePostfix(const std::string& expr) {
    std::stack<double> s;
    std::stringstream ss(expr);
    std::string token;

    while (ss >> token) {
        if (isDigit(token[0])) {
            s.push(std::stod(token));
        } else if (isOperator(token[0])) {
            double b = s.top(); s.pop();
            double a = s.top(); s.pop();
            s.push(applyOperator(a, b, token[0]));
        }
    }

    return s.top();
}

// 计算表达式
double evaluateExpression(const std::string& expr) {
    // 检查表达式是否有效
    if (!isValidExpression(expr)) {
        throw std::runtime_error("ILLEGAL");
    }

    std::string postfixExpr = infixToPostfix(expr);  // 将中缀表达式转换为后缀表达式
    return evaluatePostfix(postfixExpr);  // 计算后缀表达式的值
}

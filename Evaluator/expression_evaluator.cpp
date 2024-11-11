#include "expression_evaluator.h"
#include <cctype>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <string>
#include <regex>




std::string transformExpression(const std::string& expression) {
    std::string result = expression;
    
    // 匹配 ( -num ) 或 (-num ) 或 ( - num ) 形式的 (-num)
    std::regex pattern("\\(\\s*-\\s*(\\d+(\\.\\d+)?)\\s*\\)"); 
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
    // 使用 std::regex_iterator 迭代所有匹配项
    std::string::const_iterator searchStart = result.begin();
    std::string::const_iterator searchEnd = result.end();
    std::smatch match;
    
    // 创建一个正则表达式迭代器
    std::regex_iterator<std::string::const_iterator> iter(searchStart, searchEnd, pattern);
    std::regex_iterator<std::string::const_iterator> end;
    
    // 遍历所有匹配项
    while (iter != end) {
        match = *iter;  // 获取当前匹配
        std::string num = match.str(1);  // 获取数字部分
        
        // 将 (-num) 替换成 (0-num)
        result.replace(match.position(0), match.length(0), "(0-" + num + ")");
        
        // 更新迭代器继续匹配后续内容
        iter = std::regex_iterator<std::string::const_iterator>(result.begin(), result.end(), pattern);
    }

    return result;
}

// 用于将科学计数法字符串转换为数字
double convertScientificNotation(const std::string& str) {
    size_t ePos = str.find('e');
    if (ePos == std::string::npos) {
        ePos = str.find('E');
    }

    if (ePos != std::string::npos) {
        double base = std::stod(str.substr(0, ePos));
        int exponent = std::stoi(str.substr(ePos + 1));  // 解析指数部分
        return base * std::pow(10, exponent);
    }

    return std::stod(str);  // 如果没有科学计数法，直接转换为数字
}

// 去除字符串中的所有空格
std::string removeSpaces(const std::string& expr) {
    std::string result = expr;
    result.erase(std::remove(result.begin(), result.end(), ' '), result.end());  // 删除所有空格
    return result;
}

// 处理表达式中的科学计数法部分，将其转换为数字
std::string preprocessScientificNotation(std::string expr) {
    // Step 1: 去除所有空格
    expr = removeSpaces(expr);
    
    // Step 2: 使用正则表达式查找并处理科学计数法
    std::regex sciRegex(R"(\d+(\.\d+)?[eE][+-]?\d+)");  // 匹配科学计数法（包括负指数）
    std::smatch match;

    // 查找所有科学计数法并进行转换
    while (std::regex_search(expr, match, sciRegex)) {
        std::string sciStr = match.str();
        long double value = convertScientificNotation(sciStr);  // 转换为数字
        expr.replace(match.position(), match.length(), std::to_string(value));  // 替换原有的科学计数法
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


// 检查表达式是否有效
bool isValidExpression(const std::string& expr) {
    if (expr.empty()) {
        return false; // 空字符串不合法
    }

    size_t openParenCount = 0;
    size_t closeParenCount = 0;
    bool prevWasOperator = true; // 表达式开始时允许是运算符（考虑负号）

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        // 检查非法字符
        if (!std::isdigit(c) && !isOperator(c) && c != '(' && c != ')' && c != '.' && c != ' ') {
            return false;
        }

        // 检查括号平衡
        if (c == '(') openParenCount++;
        if (c == ')') closeParenCount++;
        if (closeParenCount > openParenCount) return false; // 右括号不能多于左括号

        // 检查连续运算符或数字
        if (isOperator(c)) {
            if (prevWasOperator && !(i > 0 && expr[i - 1] == ')')) { 
                return false;  // 如果运算符前不是操作数或右括号，则不合法
            }
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

        // 检查运算符前后是否为操作数或括号
        if (isOperator(c)) {
            // 如果运算符前不是数字、右括号或另一个括号
            if (i == 0 || (!std::isdigit(expr[i - 1]) && expr[i - 1] != ')')) {
                return false;
            }
            // 如果运算符后不是数字、左括号或另一个括号
            if (i + 1 == expr.size() || (!std::isdigit(expr[i + 1]) && expr[i + 1] != '(')) {
                return false;
            }
        }

    }

    // 最后检查括号是否匹配
    if (openParenCount != closeParenCount) {
        return false;
    }

    return true;
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

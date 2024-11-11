#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <stack>
#include <string>
#include <stdexcept>

double convertScientificNotation(const std::string& str);
std::string preprocessScientificNotation(std::string expr);
std::string transformExpression(const std::string& expression);


// 获取运算符优先级
int precedence(char op);

// 检查是否为运算符
bool isOperator(char c);

// 检查字符是否为数字或小数点
bool isDigit(char c);

// 检查输入表达式是否合法
bool isValidExpression(const std::string& expr);

// 执行运算操作
double applyOperator(double a, double b, char op);

// 中缀表达式转后缀表达式
std::string infixToPostfix(const std::string& expr);

// 后缀表达式求值
double evaluatePostfix(const std::string& expr);

// 计算表达式的结果
double evaluateExpression(const std::string& expr);

#endif // EXPRESSION_EVALUATOR_H

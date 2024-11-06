#include <iostream>
#include <string>
#include "expression_evaluator.h"
#include <vector>

int main() {


    std::string expr;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, expr);


    // 预处理表达式，处理负数和科学计数法
    expr = preprocessScientificNotation(expr);

    
    expr = transformExpression(expr);


    // 处理空输入的情况
    if (expr.empty()) {
        std::cout << "ILLEGAL" << std::endl;
        return 0;
    }

    try {
        double result = evaluateExpression(expr);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}


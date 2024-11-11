#include <iostream>
#include <string>
#include "expression_evaluator.h"
#include <vector>

int main() {

std::vector<std::string> testExpressions = {
    // **基础四则运算和括号**
    "3 / 0",                               // 除数为零
    "(-9) / (9-9)",                        // 除数为零
    "(9*(9-8*(4-2*(5-4))))+1",             // 多重括号
    "( - 6 . 3 5 8 ) * ( - 3 . 1 ) * ( 3 ) * ( - 5 . 5 )",  // 含负数和小数
    "( -10 ) + ( 20 )",                    // 基本加法，负数
    "( -1.234 ) * ( 4.56 )",               // 基本乘法，负数和小数
    "( 1.1 ) * ( - 2.2 )",                 // 乘法，负数和小数
    "( 3 )",                               // 单一数字，括号
    "( -0.5 ) / ( 2 )",                    // 除法，负数和小数
    "( - 0.2 ) + ( - 3.8 )",               // 加法，负数和小数

    // **科学计数法**
    "e-2",
    "1e-2",
    "2e2",                                 // 科学计数法，正指数
    "(-2e2)",   
    "-2e-2"  ,
    "(-2e-2)",                         // 科学计数法，负指数
    "( 1e-3 ) * ( 2E+2 )",                 // 科学计数法，负指数和正指数
    "1e+2",                                // 科学计数法，正指数
    "1E-4",                                // 科学计数法，负指数
    "5.6e-3",                              // 小数形式的科学计数法
    "2e",

    // **非法表达式**
    "(1 + 2",                              // 括号不匹配，缺少右括号
    "(1 + 2))",                             // 括号不匹配，额外的右括号
    "+1 * 2",                              // 表达式以运算符开头
    "2%9",
    "1 + * 2",                             // 运算符连续使用
    "(3 + 5",                              // 括号不匹配，缺少右括号
    "(3 + (5 - 2)",                        // 多重括号，缺少右括号
    "5 / 0",                               // 除数为零
    "(3 * 2))",                            // 括号不匹配
    "2e+2 + 3e",                           // 科学计数法表达式不完整
    "3e2+ + 4e-2",                         // 运算符连续
    "(5 / 2))",                            // 括号不匹配
    "( - 2 . 3 ) * ( - 3 . 4 ) + )",       // 括号不匹配
    "(5 + 3",                              // 括号不匹配
    "(3+5",                                // 括号不匹配
    "(-)3",                                // 不合法的负号
    "(5 +)2",                              // 运算符后没有操作数
    "2 * (3 / 0)",                         // 除数为零，带括号
    "++5",                                 // 运算符连续使用
    "-(5 * (3 + 2))",                      // 负号后面直接跟括号

    // **混合运算和边界情况**
    "1 + 2 * 3",                           // 加法和乘法混合
    "(3 + 2) * (5 - 2)",                   // 括号内的加减法和乘法
    "(1 + 2) * 3",                         // 括号内的加法和乘法
    "(10 / 2) * 3 + 5",                    // 除法与乘法混合
    "(1.23 + 4.56) * 7.89",                // 小数运算
    "(10 + 5) * (8 - 3) / 2",              // 括号和混合运算
    "(10 + (5 * 2)) / (8 - 3)",            // 多重括号与混合运算
    "(10 + 5) * (8 - 3) * (5 / 2)",        // 多重运算
    "(10 + 5) * (8 - 3) / (5 - 3)",        // 括号与运算混合，除法
    "(3.5 * 2.1) + (1.1 * 2)",             // 浮点数运算
    "(2e2 + 3.5) / 10",                    // 科学计数法和基本运算
    "(5e-2 + 10) * 2",                     // 科学计数法与加法混合
    "(2e2 * 2) / 5",                       // 科学计数法与乘法/除法混合
    "(2.2e3 + 3.3) * 1.1",                 // 科学计数法与加法
    "(1 + 1) * (2 + 2)",                   // 括号内简单运算
    "(5 + 5) / 2",                         // 简单除法
    "(10 + 2) * 5 / 4",                    // 综合运算
    "1.5 + 2.5 * (2 + 3)",                 // 小数运算和括号
    "2 * (3 + 1) * 2.5",                   // 乘法和括号

    // **非常规运算**
    "(3 + 2) * 5.5",                       // 整数和浮点数运算混合
    "(10 * 3.0) / 5",                      // 整数与浮点数混合
    "(4.0 / 2) * 3",                       // 浮点数与整数混合
    "(3 * 2.0) + 1",                       // 浮点数和整数混合
    "(10.0 / 3)",                          // 浮点数除法
    "(10 / 3.0)",                          // 整数与浮点数除法
};


    // 遍历每个表达式进行测试
    for (const auto& expr : testExpressions) {
        std::cout << "Testing expression: " << expr << std::endl;

        try {
            // 预处理表达式，处理负数和科学计数法
            std::string processedExpr = preprocessScientificNotation(expr);

            // 处理表达式中的负数并转换
            processedExpr = transformExpression(processedExpr);

            // 处理空输入的情况
            if (processedExpr.empty()) {
                std::cout << "ILLEGAL" << std::endl;
                continue;
            }

            // 计算结果并输出
            double result = evaluateExpression(processedExpr);
            std::cout << "Result: " << result << std::endl << std::endl;

        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << std::endl << std::endl;
        }
    }
    std::string expr;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, expr);


    // 预处理表达式，处理科学计数法
    expr = preprocessScientificNotation(expr);

    //处理负数
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


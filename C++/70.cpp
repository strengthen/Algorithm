#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <vector>   // 引入向量容器库，用于存储矩阵维度信息
#include <string>   // 引入字符串库，用于处理运算表达式
#include <stack>    // 引入栈容器库，用于辅助解析表达式

using namespace std; // 使用标准命名空间

// 定义一个结构体用来存储矩阵的行数和列数
struct Matrix {
    int rows; // 矩阵的行数
    int cols; // 矩阵的列数
};

int main() {
    int n; // 定义变量n，用于存储矩阵的个数
    // 使用while循环读取输入，直到输入结束，适用于多组测试用例或单组测试用例
    while (cin >> n) { 
        vector<Matrix> matrices(n); // 创建一个大小为n的vector，存储输入的n个矩阵
        for (int i = 0; i < n; ++i) { // 遍历输入每一个矩阵的维度
            cin >> matrices[i].rows >> matrices[i].cols; // 读取第i个矩阵的行数和列数
        }

        string rule; // 定义字符串变量rule，用于存储运算表达式
        cin >> rule; // 读取运算表达式

        stack<Matrix> s; // 定义一个栈，用于存储待计算的矩阵（包括原始矩阵和中间结果矩阵）
        long long totalCost = 0; // 定义总运算量变量，使用long long防止整数溢出

        // 遍历表达式字符串中的每一个字符
        for (char c : rule) {
            if (isalpha(c)) { // 如果当前字符是字母（表示一个矩阵）
                // 将对应的矩阵信息压入栈中
                // 题目约定第i个大写字母对应第i个矩阵，'A'对应索引0
                s.push(matrices[c - 'A']); 
            } else if (c == ')') { // 如果当前字符是右括号，表示一个括号内的乘法运算结束
                // 从栈中弹出两个矩阵进行计算
                // 注意栈是后进先出，所以第一次弹出的是右边的操作数矩阵
                Matrix m2 = s.top(); 
                s.pop(); // 弹出右矩阵
                
                // 第二次弹出的是左边的操作数矩阵
                Matrix m1 = s.top(); 
                s.pop(); // 弹出左矩阵

                // 计算矩阵乘法的运算量：左矩阵行数 * 左矩阵列数 * 右矩阵列数
                // 注意：矩阵乘法前提是 m1.cols == m2.rows
                totalCost += (long long)m1.rows * m1.cols * m2.cols;

                // 两个矩阵相乘后，结果矩阵的维度是：左矩阵行数 x 右矩阵列数
                Matrix result = {m1.rows, m2.cols}; 
                s.push(result); // 将结果矩阵压回栈中，供后续运算使用
            }
            // 如果是左括号 '('，不需要做任何操作，直接进入下一次循环
        }

        cout << totalCost << endl; // 输出计算得到的总运算量
    }
    
    return 0; // 程序正常结束
}

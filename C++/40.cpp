#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string> // 引入字符串库，用于处理字符串
#include <cctype> // 引入字符处理库，包含isalpha和isdigit等函数

using namespace std; // 使用标准命名空间，避免每次调用标准库都要加std::

int main() { // 主函数程序的入口
    string line; // 定义一个字符串变量line，用于存储读取的一行文本
    // 使用getline从标准输入读取一行字符串，循环直到输入结束
    while (getline(cin, line)) { 
        int letters = 0; // 定义整型变量letters，用于统计英文字母个数，初始化为0
        int spaces = 0; // 定义整型变量spaces，用于统计空格个数，初始化为0
        int digits = 0; // 定义整型变量digits，用于统计数字个数，初始化为0
        int others = 0; // 定义整型变量others，用于统计其他字符个数，初始化为0

        // 使用范围for循环遍历字符串line中的每一个字符c
        for (char c : line) { 
            if (isalpha(c)) { // 判断当前字符c是否为英文字母（包括大小写）
                letters++; // 如果是英文字母，计数器加1
            } else if (c == ' ') { // 判断当前字符c是否为空格
                spaces++; // 如果是空格，计数器加1
            } else if (isdigit(c)) { // 判断当前字符c是否为数字（0-9）
                digits++; // 如果是数字，计数器加1
            } else { // 如果不是上述任何一种情况，则归为其他字符
                others++; // 其他字符计数器加1
            } // 结束if-else条件判断
        } // 结束for循环

        cout << letters << endl; // 输出英文字母的个数，并换行
        cout << spaces << endl; // 输出空格的个数，并换行
        cout << digits << endl; // 输出数字的个数，并换行
        cout << others << endl; // 输出其他字符的个数，并换行
    } // 结束while循环

    return 0; // 主函数返回0，表示程序正常退出
} // 主函数结束


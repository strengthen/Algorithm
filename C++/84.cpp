#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串

using namespace std; // 使用标准命名空间，避免每次调用标准库函数时都需要加std::前缀

int main() { // 主函数入口
    string s; // 定义一个字符串变量s，用于存储输入的字符串
    while (getline(cin, s)) { // 使用getline函数从标准输入读取一行字符串到s中，循环读取直到输入结束
        int count = 0; // 定义一个整型变量count，用于统计大写字母的个数，初始化为0
        for (char c : s) { // 使用范围for循环遍历字符串s中的每一个字符
            if (c >= 'A' && c <= 'Z') { // 判断当前字符c是否在大写字母'A'到'Z'的范围内
                count++; // 如果是大写字母，则计数器count加1
            }
        }
        cout << count << endl; // 输出最终统计的大写字母个数，并换行
    }
    return 0; // 返回0，表示程序正常执行结束
}

#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串
#include <algorithm> // 引入算法库，用于使用reverse函数

using namespace std; // 使用标准命名空间std

int main() { // 主函数入口
    string s; // 定义一个字符串变量s，用于存储输入的字符串
    // 使用getline函数读取一行输入，直到遇到换行符
    // 题目描述中包含空格，所以不能直接用cin >> s
    while (getline(cin, s)) { // 循环读取每一行输入
        // 使用algorithm库中的reverse函数翻转字符串
        // s.begin()指向字符串起始位置，s.end()指向字符串末尾位置
        reverse(s.begin(), s.end()); // 将字符串s的内容进行原地翻转
        
        cout << s << endl; // 输出翻转后的字符串，并换行
    }
    return 0; // 返回0，表示程序正常执行完毕
}

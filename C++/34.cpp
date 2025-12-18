#include <iostream> // 包含标准输入输出流库
#include <string>   // 包含字符串处理库
#include <algorithm> // 包含算法库，用于调用排序函数

using namespace std; // 使用标准命名空间std

int main() { // 主程序的入口函数
    string s; // 声明一个字符串变量s，用来存储输入的字符串
    while (cin >> s) { // 循环读取标准输入中的字符串，直到输入结束
        sort(s.begin(), s.end()); // 调用标准库的sort函数，对字符串s中的字符按ASCII码进行升序排序
        cout << s << endl; // 将排序后的字符串输出到标准输出，并换行
    } // while循环结束
    return 0; // 返回0，表示程序执行成功
}


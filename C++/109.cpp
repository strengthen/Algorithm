#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串库
#include <unordered_set> // 引入无序集合库，用于去重

using namespace std; // 使用标准命名空间

int main() {
    string s; // 定义字符串变量s
    while (cin >> s) { // 循环读取输入字符串
        unordered_set<char> unique_chars; // 定义字符集合，用于存储出现的不同字符
        for (char c : s) { // 遍历字符串中的每个字符
            unique_chars.insert(c); // 将字符插入集合，自动去重
        }
        cout << unique_chars.size() << endl; // 输出集合的大小，即不同字符的个数
    }
    return 0; // 程序正常结束
}

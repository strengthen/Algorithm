#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串对象
#include <vector>   // 引入向量库，虽然本题主要用数组，但作为常用库可以引入

using namespace std; // 使用标准命名空间，避免每次调用标准库函数时都要加 std::

// 主函数，程序的入口点
int main() {
    string s; // 定义字符串变量 s，用于存储需要检查的短字符串
    string t; // 定义字符串变量 t，用于存储包含字符的长字符串

    // 使用 while 循环读取输入，cin >> s >> t 会自动跳过空白字符读取两个字符串
    // 这样可以处理包含多组测试用例的情况
    while (cin >> s >> t) {
        // 定义一个布尔类型的数组，大小为 26，对应 26 个小写英文字母
        // 用于标记字符串 t 中出现了哪些字符
        bool existsInT[26] = {false}; 

        // 遍历字符串 t 中的每一个字符
        for (char c : t) {
            // 计算字符 c 对应的索引（'a' 对应 0，'b' 对应 1，以此类推）
            // 并将该位置标记为 true，表示该字符在 t 中存在
            existsInT[c - 'a'] = true; 
        }

        bool allFound = true; // 定义一个标志变量，初始设为 true，假设 s 中所有字符都在 t 中存在

        // 遍历字符串 s 中的每一个字符
        for (char c : s) {
            // 检查当前字符 c 是否在 t 中出现过（即对应的 existsInT 数组位置是否为 true）
            if (!existsInT[c - 'a']) {
                allFound = false; // 如果字符 c 在 t 中不存在，将标志变量设为 false
                break; // 只要发现一个字符不存在，就可以跳出循环，不需要继续检查了
            }
        }

        // 根据标志变量 allFound 的值输出结果
        if (allFound) {
            cout << "true" << endl; // 如果 s 中所有字符都在 t 中，输出 true
        } else {
            cout << "false" << endl; // 否则输出 false
        }
    }

    return 0; // 程序执行成功，返回 0
}

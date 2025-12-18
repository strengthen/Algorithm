#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串操作
#include <unordered_map> // 引入无序哈希表库，用于统计字符出现的次数

using namespace std; // 使用标准命名空间，避免每次调用标准库函数时都需要加std::前缀

int main() { // 主函数，程序的入口点
    string s; // 定义一个字符串变量s，用于存储输入的字符串
    
    // 尝试从标准输入读取一个字符串到s中
    // 题目描述输入在一行上，cin >> s 会读取直到空白字符，适合本题
    if (cin >> s) { 
        unordered_map<char, int> charCount; // 定义一个哈希表，键是字符char，值是整数int，用于存储每个字符出现的次数
        
        // 第一步：遍历字符串，统计每个字符出现的频率
        for (char c : s) { // 使用范围for循环遍历字符串s中的每一个字符c
            charCount[c]++; // 将当前字符c在哈希表中的计数加1。如果c不存在，会默认初始化为0再加1
        }
        
        bool found = false; // 定义一个布尔变量found，标记是否找到了只出现一次的字符，初始化为false
        
        // 第二步：再次遍历字符串，找出第一个出现次数为1的字符
        // 必须按字符串顺序遍历，以保证找到的是“第一个”
        for (char c : s) { // 再次使用范围for循环遍历字符串s中的每一个字符c
            if (charCount[c] == 1) { // 检查当前字符c在哈希表中的计数是否等于1
                cout << c << endl; // 如果等于1，说明它是第一个只出现一次的字符，输出该字符
                found = true; // 将找到标记设为true
                break; // 找到后立即跳出循环，因为只需要第一个
            }
        }
        
        // 如果遍历完字符串都没有找到只出现一次的字符
        if (!found) { // 检查found标记是否仍为false
            cout << -1 << endl; // 如果没找到，按照题目要求输出-1
        }
    }
    
    return 0; // 程序正常结束，返回0
}

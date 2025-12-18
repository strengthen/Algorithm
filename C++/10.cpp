#include <iostream> // 引入标准输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串数据
#include <set>      // 引入集合库，std::set 具有自动去重的功能

using namespace std; // 使用标准命名空间 std，方便直接使用 string, set, cout 等

int main() { // 主函数，程序的入口点
    string input_str; // 声明一个字符串变量 input_str，用于存储输入的字符串
    
    // 使用 getline 从标准输入读取一行字符串，可以包含空格（虽然题目说不含空格，但这样更通用）
    getline(cin, input_str); 
    
    set<char> char_set; // 声明一个字符集合 char_set，用于存储出现过的不同字符

    // 使用范围 for 循环遍历输入字符串中的每一个字符 c
    for (char c : input_str) {
        // 判断字符 c 的 ASCII 码值是否在 0 到 127 之间
        // 题目要求统计 ASCII 码在 0-127 范围内的字符
        if (c >= 0 && c <= 127) {
            char_set.insert(c); // 将字符 c 插入到集合中
            // 如果集合中已经存在该字符，insert 操作不会添加重复元素，从而实现去重
        }
    }

    // 输出集合的大小，即不同字符的个数
    cout << char_set.size() << endl;

    return 0; // 程序执行成功，返回 0
}





#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于使用string类型
#include <cctype>   // 引入字符处理库，用于使用tolower函数

using namespace std; // 使用标准命名空间，避免每次调用标准库函数都加std::

int main() { // 主函数入口，程序从这里开始执行
    string s; // 声明一个字符串变量s，用于存储第一行输入的字符串
    getline(cin, s); // 从标准输入读取一行字符串（包含空格）存入s中

    char c; // 声明一个字符变量c，用于存储第二行输入的特定字符
    cin >> c; // 从标准输入读取该字符

    int count = 0; // 声明一个整型变量count用于计数，初始化为0
    
    // 将目标字符转换为小写。注意：如果是数字，tolower会直接返回原数字字符
    char target = tolower(c); // 调用tolower函数将字符c转换为小写并赋值给target

    // 使用for循环遍历字符串s中的每一个字符
    for (int i = 0; i < s.length(); ++i) { // i从0开始，直到小于字符串s的长度，每次循环i加1
        // 将当前遍历到的字符s[i]也转换为小写，然后与目标字符target进行比较
        if (tolower(s[i]) == target) { // 如果转换后相等（实现了不区分大小写匹配）
            count++; // 计数器count的值加1
        } // if语句块结束
    } // for循环结束

    cout << count << endl; // 将最终的统计结果count输出到控制台，并输出一个换行符

    return 0; // 主函数返回0，表示程序正常结束
} // main函数结束


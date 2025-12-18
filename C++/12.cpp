#include <iostream> // 引入标准输入输出流库，用于cin和cout
#include <string>   // 引入字符串库，用于使用string类型
#include <algorithm> // 引入算法库，用于使用reverse反转函数

using namespace std; // 使用标准命名空间std，方便直接使用库中的名称

int main() { // 主函数的入口点
    string s; // 声明一个字符串变量s，用于存储输入的字符串
    
    // 从标准输入读取字符串。题目描述为一行输入。
    // cin >> s 会自动跳过前导空白字符，并在遇到下一个空白字符时停止读取。
    if (cin >> s) { // 尝试读取输入，如果读取成功则执行块内代码
        // 使用std::reverse函数反转字符串
        // s.begin() 返回指向字符串第一个字符的迭代器
        // s.end() 返回指向字符串最后一个字符之后位置的迭代器
        reverse(s.begin(), s.end()); // 将字符串s在区间[begin, end)内的字符顺序进行反转
        
        cout << s << endl; // 将反转后的字符串s输出到屏幕，并输出换行符
    } // if代码块结束

    return 0; // 返回0，表示程序成功执行完毕
} // main函数结束





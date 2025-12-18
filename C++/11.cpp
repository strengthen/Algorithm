#include <iostream> // 包含标准输入输出流库，用于控制台的输入和输出操作
#include <string>   // 包含字符串处理库，用于定义和操作string类型的变量
#include <algorithm> // 包含标准算法库，本题中主要用于调用reverse反转函数

using namespace std; // 使用标准命名空间std，避免在代码中频繁使用std::前缀

int main() { // 主函数，程序的执行入口
    string str_num; // 定义一个字符串变量str_num，用来存储输入的数字
    
    cin >> str_num; // 从标准输入流读取一个字符串，遇到空白字符停止
    
    // 使用reverse函数对字符串进行原地反转
    // str_num.begin()是字符串的起始位置迭代器
    // str_num.end()是字符串的结束位置迭代器
    reverse(str_num.begin(), str_num.end()); 
    
    cout << str_num << endl; // 将反转后的字符串输出到标准输出流，并换行
    
    return 0; // 返回整数0，表示程序成功执行并退出
}





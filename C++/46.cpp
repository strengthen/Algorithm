#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串处理库
using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    string s; // 声明一个字符串变量s用于存储输入的字符串
    int k; // 声明一个整型变量k用于存储截取的长度
    
    // 循环读取输入，cin >> s >> k 会跳过空白字符读取字符串和整数
    // while循环确保如果有多组测试数据也能正常处理
    while (cin >> s >> k) { 
        // 使用string类的substr成员函数截取子串
        // substr(0, k) 表示从索引0开始截取长度为k的字符串
        string result = s.substr(0, k); // 获取截取后的字符串
        
        // 输出截取后的字符串
        cout << result << endl; // 输出结果并换行
    }
    
    return 0; // 程序正常结束，返回0
}


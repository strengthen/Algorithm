#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串库

using namespace std; // 使用标准命名空间

int main() {
    string s; // 定义一个字符串变量s，用于存储输入的十六进制数
    
    // 循环读取输入，直到输入结束。这样可以处理多组测试数据。
    while (cin >> s) {
        long long result = 0; // 定义一个长整型变量result，用于存储转换后的十进制结果，防止溢出
        
        // 遍历字符串s，从下标2开始，因为题目说明输入以 "0x" 开头
        for (size_t i = 2; i < s.length(); ++i) {
            int digit = 0; // 定义一个整型变量digit，用于存储当前字符代表的数值
            
            // 判断当前字符是否为数字 '0' 到 '9'
            if (s[i] >= '0' && s[i] <= '9') {
                digit = s[i] - '0'; // 将字符转换为对应的数值 (例如 '1' -> 1)
            }
            // 判断当前字符是否为大写字母 'A' 到 'F'
            else if (s[i] >= 'A' && s[i] <= 'F') {
                digit = s[i] - 'A' + 10; // 将字符转换为对应的数值 (例如 'A' -> 10)
            }
            // 判断当前字符是否为小写字母 'a' 到 'f' (题目虽未明确提及小写，但增加此判断更稳健)
            else if (s[i] >= 'a' && s[i] <= 'f') {
                digit = s[i] - 'a' + 10; // 将字符转换为对应的数值 (例如 'a' -> 10)
            }
            
            // 核心转换逻辑：将旧结果左移一位（乘以16），然后加上当前位的数值
            // 这相当于 result = result * 16 + digit
            result = result * 16 + digit; 
        }
        
        // 输出最终计算得到的十进制数
        cout << result << endl;
    }
    
    return 0; // 程序正常结束
}


#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串处理库
#include <vector>   // 引入向量容器库
#include <algorithm> // 引入算法库，用于排序
#include <cctype>   // 引入字符处理库，如isdigit等

using namespace std; // 使用标准命名空间

// 辅助函数：处理单个字符的转换逻辑
// 输入一个字符，返回处理后的字符
char process_char(char c) { // 定义处理字符的函数
    int val = -1; // 用于存储字符对应的十进制数值，初始化为-1
    
    // 判断字符是否为数字
    if (c >= '0' && c <= '9') { // 如果是数字字符
        val = c - '0'; // 转换为对应的整数
    } 
    // 判断字符是否为小写十六进制字母
    else if (c >= 'a' && c <= 'f') { // 如果是 'a'-'f'
        val = c - 'a' + 10; // 转换为对应的整数 (10-15)
    } 
    // 判断字符是否为大写十六进制字母
    else if (c >= 'A' && c <= 'F') { // 如果是 'A'-'F'
        val = c - 'A' + 10; // 转换为对应的整数 (10-15)
    } 
    // 如果不是合法的十六进制字符
    else { // 如果都不匹配
        return c; // 直接返回原字符，不做处理
    }

    // 将十进制数转换为4位二进制并翻转
    int reversed_val = 0; // 用于存储翻转后的数值
    
    // 检查第0位（最低位）是否为1
    if (val & 1) reversed_val |= 8; // 如果是，则将结果的第3位（最高位）置为1 (8是1000)
    // 检查第1位是否为1
    if (val & 2) reversed_val |= 4; // 如果是，则将结果的第2位置为1 (4是0100)
    // 检查第2位是否为1
    if (val & 4) reversed_val |= 2; // 如果是，则将结果的第1位置为1 (2是0010)
    // 检查第3位（最高位）是否为1
    if (val & 8) reversed_val |= 1; // 如果是，则将结果的第0位置为1 (1是0001)

    // 将翻转后的数值转换回大写十六进制字符
    if (reversed_val >= 0 && reversed_val <= 9) { // 如果数值在0-9之间
        return reversed_val + '0'; // 转换为对应的数字字符
    } else { // 如果数值在10-15之间
        return reversed_val - 10 + 'A'; // 转换为对应的十六进制大写字母
    }
}

// 主函数
int main() { // 程序入口
    string s, t; // 定义两个字符串变量 s 和 t 用于接收输入
    
    // 循环读取输入，直到没有更多输入
    while (cin >> s >> t) { // 从标准输入读取 s 和 t
        // 第一步：合并字符串
        string u = s + t; // 将 t 拼接到 s 后面，赋值给 u
        
        // 准备分离奇数位和偶数位字符进行排序
        // 题目中下标从1开始，所以题目中的奇数位对应程序下标的偶数位（0, 2, ...）
        // 题目中的偶数位对应程序下标的奇数位（1, 3, ...）
        string odd_pos_chars = ""; // 用于存储题目所述奇数位（程序下标偶数位）的字符
        string even_pos_chars = ""; // 用于存储题目所述偶数位（程序下标奇数位）的字符
        
        // 遍历合并后的字符串 u
        for (int i = 0; i < u.length(); ++i) { // 从索引 0 开始遍历
            if (i % 2 == 0) { // 如果是程序下标的偶数位（题目奇数位）
                odd_pos_chars += u[i]; // 添加到奇数位字符集
            } else { // 如果是程序下标的奇数位（题目偶数位）
                even_pos_chars += u[i]; // 添加到偶数位字符集
            }
        }
        
        // 分别对两组字符进行排序
        sort(odd_pos_chars.begin(), odd_pos_chars.end()); // 对奇数位字符集进行升序排序
        sort(even_pos_chars.begin(), even_pos_chars.end()); // 对偶数位字符集进行升序排序
        
        // 将排序后的字符放回原字符串对应的位置
        int odd_idx = 0; // 奇数位字符集的读取指针
        int even_idx = 0; // 偶数位字符集的读取指针
        
        for (int i = 0; i < u.length(); ++i) { // 再次遍历 u 的长度
            if (i % 2 == 0) { // 如果是程序下标的偶数位
                u[i] = odd_pos_chars[odd_idx++]; // 填入排序后的奇数位字符，指针后移
            } else { // 如果是程序下标的奇数位
                u[i] = even_pos_chars[even_idx++]; // 填入排序后的偶数位字符，指针后移
            }
        }
        
        // 第二阶段：调整转换
        for (int i = 0; i < u.length(); ++i) { // 遍历排序后的字符串 u
            u[i] = process_char(u[i]); // 对每个字符调用处理函数进行转换
        }
        
        // 输出最终结果
        cout << u << endl; // 打印处理后的字符串并换行
    }
    
    return 0; // 程序正常结束
}


#include <iostream> // 包含输入输出流库

using namespace std; // 使用标准命名空间

int main() { // 主函数入口
    int n; // 定义一个整型变量n，用于存储输入的十进制整数
    while (cin >> n) { // 循环读取输入，直到没有输入为止
        int max_len = 0; // 定义变量max_len，用于记录最长连续1的长度，初始化为0
        int current_len = 0; // 定义变量current_len，用于记录当前连续1的长度，初始化为0
        
        while (n > 0) { // 当n大于0时，进行循环处理
            if (n & 1) { // 判断n的二进制表示的最低位是否为1
                current_len++; // 如果最低位是1，当前连续1的长度加1
            } else { // 如果最低位不是1（即为0）
                if (current_len > max_len) { // 如果当前连续1的长度大于已记录的最长长度
                    max_len = current_len; // 更新最长连续1的长度
                }
                current_len = 0; // 重置当前连续1的长度为0
            }
            n >>= 1; // 将n的二进制表示向右移动一位，相当于除以2
        }
        
        // 循环结束后，可能最后一段连续的1是最长的，需要再次判断
        if (current_len > max_len) { // 如果最后的当前连续1的长度大于最长长度
            max_len = current_len; // 更新最长连续1的长度
        }
        
        cout << max_len << endl; // 输出最长连续1的长度，并换行
    }
    return 0; // 程序正常结束，返回0

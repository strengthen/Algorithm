#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串
#include <algorithm> // 引入算法库，用于使用max函数

using namespace std; // 使用标准命名空间，避免每次调用标准库函数时都需要加std::前缀

// 主函数，程序的入口
int main() {
    string s; // 定义一个字符串变量s，用于存储输入的字符串
    
    // 循环读取输入，虽然题目通常只输入一行，但这样写可以处理多组测试数据
    while (cin >> s) {
        int n = s.length(); // 获取字符串的长度
        int maxLen = 0; // 初始化最长回文子串的长度为0，用于记录结果

        // 遍历字符串的每一个字符，将其作为回文中心进行尝试（中心扩展法）
        for (int i = 0; i < n; ++i) {
            
            // 第一种情况：回文子串长度为奇数，以当前字符s[i]为中心
            int left = i; // 左指针初始化指向当前字符
            int right = i; // 右指针初始化指向当前字符
            
            // 向左右两边扩展，条件是索引不越界且左右两边的字符相等
            while (left >= 0 && right < n && s[left] == s[right]) {
                left--; // 左指针向左移动一位
                right++; // 右指针向右移动一位
            }
            // 当循环结束时，s[left] 和 s[right] 不相等或者越界
            // 此时有效回文范围是 [left+1, right-1]
            // 长度计算公式为：(right - 1) - (left + 1) + 1 = right - left - 1
            int currentLen = right - left - 1; // 计算当前奇数长度回文串的长度
            if (currentLen > maxLen) { // 如果当前长度大于已记录的最大长度
                maxLen = currentLen; // 更新最大长度
            }

            // 第二种情况：回文子串长度为偶数，以当前字符s[i]和下一个字符s[i+1]之间的空隙为中心
            left = i; // 左指针指向当前字符
            right = i + 1; // 右指针指向下一个字符
            
            // 向左右两边扩展，条件是索引不越界且左右两边的字符相等
            while (left >= 0 && right < n && s[left] == s[right]) {
                left--; // 左指针向左移动一位
                right++; // 右指针向右移动一位
            }
            // 同样计算长度，公式相同：right - left - 1
            currentLen = right - left - 1; // 计算当前偶数长度回文串的长度
            if (currentLen > maxLen) { // 如果当前长度大于已记录的最大长度
                maxLen = currentLen; // 更新最大长度
            }
        }

        // 输出最终找到的最长回文子串的长度
        cout << maxLen << endl;
    }

    return 0; // 程序正常结束返回0
}

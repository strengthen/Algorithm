#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串
#include <vector>   // 引入向量库（虽然本题可以用基础数组，但vector更常用）
#include <algorithm> // 引入算法库，用于使用max等函数

using namespace std; // 使用标准命名空间，方便直接使用string, cin, cout等

// 辅助函数：中心扩展法寻找最长回文子串的长度
// 参数 s: 输入的字符串
// 参数 left: 扩展的左边界起始位置
// 参数 right: 扩展的右边界起始位置
int expandAroundCenter(const string& s, int left, int right) {
    // 当左右边界在字符串范围内，且左右字符相等时，继续向外扩展
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
        left--;     // 左边界向左移动
        right++;    // 右边界向右移动
    }
    // 当循环结束时，s[left] 和 s[right] 不相等或越界
    // 回文串的有效部分是 [left + 1, right - 1]
    // 长度计算为 (right - 1) - (left + 1) + 1 = right - left - 1
    return right - left - 1;
}

int main() {
    string s; // 定义字符串变量用于存储输入
    
    // 循环读取每一行输入（题目虽然可能只有一组数据，但循环读取更健壮）
    while (getline(cin, s)) {
        // 如果字符串为空，直接输出0并继续
        if (s.empty()) {
            cout << 0 << endl;
            continue;
        }

        int maxLength = 0; // 用于记录找到的最长回文子串的长度

        // 遍历字符串的每一个字符，将其作为回文串的中心
        for (int i = 0; i < s.length(); ++i) {
            // 情况1：回文串长度为奇数，以当前字符 s[i] 为中心
            // 例如 "aba"，中心是 'b'
            int len1 = expandAroundCenter(s, i, i);
            
            // 情况2：回文串长度为偶数，以 s[i] 和 s[i+1] 之间的空隙为中心
            // 例如 "abba"，中心是两个 'b'
            int len2 = expandAroundCenter(s, i, i + 1);

            // 取两种情况中的较大值
            int currentMax = max(len1, len2);
            
            // 如果当前找到的回文串长度比之前记录的最大长度还大，则更新
            if (currentMax > maxLength) {
                maxLength = currentMax;
            }
        }

        // 输出最终找到的最长有效密码串（回文子串）的长度
        cout << maxLength << endl;
    }

    return 0; // 程序正常结束
}


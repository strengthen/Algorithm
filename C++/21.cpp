#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string s;
    // 循环读取输入，直到没有更多输入为止
    while (cin >> s) {
        // 遍历字符串中的每一个字符
        for (int i = 0; i < s.length(); ++i) {
            // 如果是大写字母
            if (isupper(s[i])) {
                // 先转换为小写，如果不是 'Z'，则向后移动一位（ASCII码加1）
                if (s[i] != 'Z') {
                    s[i] = tolower(s[i]) + 1;
                } else {
                    // 特殊情况：'Z' 转换为 'z' 后再向后移动一位变为 'a'
                    s[i] = 'a';
                }
            }
            // 如果是小写字母，根据手机键盘映射转换为对应的数字
            else if (islower(s[i])) {
                if (s[i] >= 'a' && s[i] <= 'c') {
                    s[i] = '2';
                } else if (s[i] >= 'd' && s[i] <= 'f') {
                    s[i] = '3';
                } else if (s[i] >= 'g' && s[i] <= 'i') {
                    s[i] = '4';
                } else if (s[i] >= 'j' && s[i] <= 'l') {
                    s[i] = '5';
                } else if (s[i] >= 'm' && s[i] <= 'o') {
                    s[i] = '6';
                } else if (s[i] >= 'p' && s[i] <= 's') {
                    s[i] = '7';
                } else if (s[i] >= 't' && s[i] <= 'v') {
                    s[i] = '8';
                } else if (s[i] >= 'w' && s[i] <= 'z') {
                    s[i] = '9';
                }
            }
            // 数字和其他字符保持不变，不做处理
        }
        // 输出变换后的字符串
        cout << s << endl;
    }
    return 0;
}


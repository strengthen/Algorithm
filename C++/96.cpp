#include <iostream> // 引入输入输出流库
#include <string>   // 引入字符串库
#include <cctype>   // 引入字符处理库，用于isdigit函数

using namespace std; // 使用标准命名空间

int main() {
    string s; // 定义一个字符串变量用于存储输入
    // 循环读取输入，直到没有更多输入为止
    while (cin >> s) {
        string result = ""; // 定义一个字符串变量用于存储处理后的结果
        // 遍历输入字符串的每一个字符
        for (int i = 0; i < s.length(); ++i) {
            // 判断当前字符是否为数字
            if (isdigit(s[i])) {
                // 如果当前是第一个字符，或者前一个字符不是数字
                if (i == 0 || !isdigit(s[i - 1])) {
                    result += '*'; // 在数字序列开始前添加一个星号
                }
                result += s[i]; // 将当前数字字符添加到结果字符串中
                // 如果当前是最后一个字符，或者后一个字符不是数字
                if (i == s.length() - 1 || !isdigit(s[i + 1])) {
                    result += '*'; // 在数字序列结束后添加一个星号
                }
            } else {
                // 如果当前字符不是数字，直接添加到结果字符串中
                result += s[i];
            }
        }
        cout << result << endl; // 输出处理后的字符串并换行
    }
    return 0; // 程序正常结束
}

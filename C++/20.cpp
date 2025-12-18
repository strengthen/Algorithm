#include <iostream> // 引入输入输出流库，用于控制台输入输出
#include <string>   // 引入字符串库，用于处理字符串对象
#include <cctype>   // 引入字符处理库，用于检查字符类型（如是否为大写、数字等）

using namespace std; // 使用标准命名空间，避免每次调用标准库函数时都要加std::

// 定义一个函数用于检查密码是否符合要求
bool check(string s) {
    // 检查条件1：密码长度必须大于8位
    if (s.length() <= 8) { // 如果字符串长度小于或等于8
        return false; // 返回false，表示密码不合格
    }

    // 检查条件2：必须包含大写字母、小写字母、数字、特殊字符中的至少三种
    int upper = 0, lower = 0, digit = 0, other = 0; // 初始化四个变量分别记录四种字符是否存在
    for (int i = 0; i < s.length(); i++) { // 遍历字符串中的每一个字符
        if (isupper(s[i])) // 如果当前字符是大写字母
            upper = 1; // 标记大写字母存在
        else if (islower(s[i])) // 否则，如果当前字符是小写字母
            lower = 1; // 标记小写字母存在
        else if (isdigit(s[i])) // 否则，如果当前字符是数字
            digit = 1; // 标记数字存在
        else // 否则（即为特殊字符）
            other = 1; // 标记特殊字符存在
    }
    
    // 计算存在的字符种类数量
    if (upper + lower + digit + other < 3) { // 如果种类总和小于3
        return false; // 返回false，表示密码不合格
    }

    // 检查条件3：不能包含长度超过2的两个相同子串（即长度为3的重复子串）
    // 只需要检查是否存在长度为3的重复子串即可，因为更长的重复子串必然包含长度为3的重复子串
    for (int i = 0; i < s.length() - 3; i++) { // 遍历字符串，直到倒数第4个字符（确保剩余长度足够截取3个字符）
        string sub = s.substr(i, 3); // 截取从当前位置i开始，长度为3的子串
        // 在字符串中从位置i+3开始查找该子串sub
        // string::npos 是一个常数，表示未找到匹配项
        if (s.find(sub, i + 3) != string::npos) { // 如果在后续部分找到了相同的子串
            return false; // 返回false，表示密码不合格
        }
    }

    return true; // 如果所有检查都通过，返回true，表示密码合格
}

int main() {
    string s; // 定义一个字符串变量用于存储输入的密码
    // 循环读取输入，直到遇到文件结束符（EOF）
    // cin >> s 会自动跳过空白字符读取下一个字符串
    while (cin >> s) { 
        if (check(s)) // 调用check函数检查当前输入的密码
            cout << "OK" << endl; // 如果合格，输出"OK"并换行
        else
            cout << "NG" << endl; // 如果不合格，输出"NG"并换行
    }
    return 0; // 主函数返回0，表示程序正常结束
}

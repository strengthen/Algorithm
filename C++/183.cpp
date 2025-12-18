#include <iostream> // 引入输入输出流库
#include <string> // 引入字符串库
#include <vector> // 引入向量库

using namespace std; // 使用标准命名空间

// 解决单个测试用例的函数
void solve() { // 定义solve函数
    string s; // 定义字符串s用于存储第一个输入字符串
    cin >> s; // 从标准输入读取字符串s
    string t; // 定义字符串t用于存储第二个输入字符串
    cin >> t; // 从标准输入读取字符串t
    
    int n = s.length(); // 获取字符串s的长度
    int m = t.length(); // 获取字符串t的长度
    int j = 0; // 初始化t的下标指针j为0

    // 遍历字符串s
    for (int i = 0; i < n; ++i) { // 使用i作为循环变量遍历s
        // 检查是否还没完全匹配完t
        if (j < m) { // 如果j小于m，说明t还有字符未匹配
            // 如果s当前字符是问号
            if (s[i] == '?') { // 判断s的第i个字符是否为'?'
                s[i] = t[j]; // 将s[i]替换为t[j]，贪心地匹配
                j++; // 匹配成功，t的指针后移
            } 
            // 如果s当前字符已经是我们需要的t[j]
            else if (s[i] == t[j]) { // 判断s[i]是否等于t[j]
                j++; // 匹配成功，t的指针后移
            }
        } else { // 如果t已经完全匹配完了
            // 剩下的问号可以替换为任意字符，这里统一换成'a'
            if (s[i] == '?') { // 判断s[i]是否为'?'
                s[i] = 'a'; // 将s[i]替换为'a'
            }
        }
    }
    
    // 检查是否成功匹配了整个字符串t
    if (j == m) { // 如果j等于m，说明t的所有字符都匹配上了
        cout << "YES" << endl; // 输出YES
        cout << s << endl; // 输出修改后的字符串s
    } else { // 否则说明无法匹配
        cout << "NO" << endl; // 输出NO
    }
}

// 主函数
int main() { // 程序入口点
    ios::sync_with_stdio(false); // 关闭C++标准流与C标准流的同步，加速I/O
    cin.tie(nullptr); // 解除cin和cout的绑定，加速I/O
    int T; // 定义变量T存储测试用例数量
    cin >> T; // 读取测试用例数量
    // 循环处理每个测试用例
    while (T--) { // 当T大于0时循环，每次递减
        solve(); // 调用solve函数处理当前测试用例
    }
    return 0; // 返回0表示程序正常结束
}

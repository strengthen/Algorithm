#include <iostream> // 引入输入输出流库，用于控制台读写
#include <string>   // 引入字符串库，用于处理字符串数据
#include <vector>   // 引入向量容器库，用于创建动态规划表
#include <cctype>   // 引入字符处理库，用于tolower和isalnum函数

using namespace std; // 使用标准命名空间，简化代码书写

int main() { // 主函数，程序的执行入口
    string s, p; // 定义两个字符串变量，s表示通配符模式串，p表示目标匹配串
    
    // 使用cin读取两个字符串，cin会自动跳过空白符
    if (cin >> s >> p) {
        int n = s.length(); // 获取通配符字符串s的长度
        int m = p.length(); // 获取目标字符串p的长度
        
        // 创建一个二维布尔类型的动态规划表dp
        // dp[i][j] 表示 s的前i个字符 是否能匹配 p的前j个字符
        // 大小初始化为 (n+1) x (m+1)，所有元素默认初始化为 false
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        
        // 初始化基础状态：空模式串匹配空目标串，结果为真
        dp[0][0] = true;
        
        // 初始化第一列：处理模式串s匹配空目标串的情况
        // 只有当模式串的前缀全是 '*' 时，才能匹配空字符串
        for (int i = 1; i <= n; ++i) {
            if (s[i-1] == '*') { // 如果当前模式字符是 '*'
                dp[i][0] = dp[i-1][0]; // 它的匹配状态取决于去掉这个 '*' 后的状态
            } else {
                break; // 一旦遇到非 '*' 字符，后续都不可能匹配空串，直接结束循环
            }
        }
        
        // 动态规划填表过程
        for (int i = 1; i <= n; ++i) { // 遍历模式串s的每一个字符
            for (int j = 1; j <= m; ++j) { // 遍历目标串p的每一个字符
                char sc = s[i-1]; // 获取当前模式字符（注意字符串下标从0开始，dp下标从1开始）
                char pc = p[j-1]; // 获取当前目标字符
                
                if (sc == '*') { // 情况1：如果模式字符是 '*'
                    // '*' 可以匹配空字符（即忽略这个 '*'），此时状态为 dp[i-1][j]
                    // '*' 也可以匹配一个或多个字符，前提是当前目标字符pc必须是数字或字母
                    // 并且 '*' 在匹配掉 pc 之前也能匹配 p 的前缀（即 dp[i][j-1]）
                    bool matchEmpty = dp[i-1][j];
                    bool matchOneOrMore = dp[i][j-1] && isalnum(pc);
                    dp[i][j] = matchEmpty || matchOneOrMore;
                } else if (sc == '?') { // 情况2：如果模式字符是 '?'
                    // '?' 只能匹配一个字符，且该字符必须是数字或字母
                    if (isalnum(pc)) {
                        dp[i][j] = dp[i-1][j-1]; // 如果匹配成功，状态继承自去掉这两个字符后的状态
                    }
                } else { // 情况3：普通字符
                    // 不区分大小写进行比较
                    // 如果字符相等（忽略大小写），则状态继承自 dp[i-1][j-1]
                    if (tolower(sc) == tolower(pc)) {
                        dp[i][j] = dp[i-1][j-1];
                    }
                }
            }
        }
        
        // 输出最终匹配结果
        if (dp[n][m]) { // 如果 dp[n][m] 为 true
            cout << "true" << endl; // 输出字符串 "true"
        } else {
            cout << "false" << endl; // 否则输出字符串 "false"
        }
    }
    
    return 0; // 程序正常退出
}

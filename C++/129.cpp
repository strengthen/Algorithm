#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 检查字符串s是否是合法的双生数
// 该函数用于验证一个字符串是否满足题目定义的"双生数"条件
bool isTwin(const string& s) {
    // 获取字符串的长度
    int n = s.length();
    // 双生数的长度必须是偶数，因为数字是成对出现的
    if (n % 2 != 0) return false;
    
    // 遍历每一个对子 (0,1), (2,3), ...
    for (int i = 0; i < n; i += 2) {
        // 每一对的两个数字必须相同，例如 "11", "22"
        if (s[i] != s[i+1]) return false;
        // 如果不是第一对，当前对的数字必须与前一对不同
        // 例如 "1111" 是非法的，因为中间的1的相邻数位有两个1
        if (i > 0 && s[i] == s[i-2]) return false;
    }
    // 如果所有检查都通过，则是合法的双生数
    return true;
}

// 生成指定长度的最小双生数
// 当输入的数长度为奇数或无法在同长度下找到更大双生数时使用
string getSmallest(int len) {
    // 长度必须为正
    if (len <= 0) return "";
    string res = "";
    // 双生数不能包含前导零，所以第一对最小只能是 "11"
    res += "11";
    // 记录上一对的数字，用于生成不同的下一对
    int last = 1;
    // 从第二对开始填充
    for (int i = 2; i < len; i += 2) {
        // 为了使数值最小，我们尽量在 00 和 11 之间交替
        // 如果上一对是 11，这一对就填 00
        if (last == 1) {
            res += "00";
            last = 0;
        } else {
            // 如果上一对是 00，这一对就填 11
            res += "11";
            last = 1;
        }
    }
    // 返回生成的最小双生数
    return res;
}

int main() {
    // 优化 C++ 标准流的 I/O 性能，避免超时
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string x;
    // 读取输入的正整数 x
    if (!(cin >> x)) return 0;

    int n = x.length();

    // 如果 x 的长度是奇数
    // 长度为 L 的奇数，其最小的双生数长度必定是 L+1
    // 因为长度为 L 的数中不存在双生数（长度必须偶数）
    // 而长度为 L+1 的最小双生数肯定大于长度为 L 的任何数
    if (n % 2 != 0) {
        cout << getSmallest(n + 1) << endl;
        return 0;
    }

    // 如果 x 本身已经是一个合法的双生数
    // 题目要求寻找不小于 x 的最小双生数，x 自身即满足
    if (isTwin(x)) {
        cout << x << endl;
        return 0;
    }

    // 如果 x 长度是偶数且不是双生数，我们需要找到一个大于 x 的最小双生数
    // 我们尝试保持 x 的前缀尽可能长，只在某一对上变大
    
    // 首先计算 x 的最长合法前缀对数 L
    // 即 x[0...2*L-1] 满足双生数的前缀性质
    int L = 0;
    for (int i = 0; i < n; i += 2) {
        // 检查当前对是否由两个相同数字组成
        bool validPair = (x[i] == x[i+1]);
        // 检查当前对是否与前一对不同（如果存在前一对）
        bool diffFromPrev = (i == 0 || x[i] != x[i-2]);
        
        // 如果满足条件，说明这一对可以保留作为前缀的一部分
        if (validPair && diffFromPrev) {
            L++; 
        } else {
            // 一旦遇到不满足条件的对，后面的都无需检查，前缀中断
            break; 
        }
    }

    // 我们从最长的合法前缀位置 L 开始，尝试寻找一个“拐点”
    // 也就是在第 k 对位置，放置一个比 x 原本该位置数值更大的合法对子
    // 为了使结果最小，我们希望这个拐点尽可能靠后（即 k 尽可能大）
    // 所以从 L 递减循环到 0
    for (int k = L; k >= 0; k--) {
        // 如果 k 越界（理论上循环条件控制了，但做个防御性编程）
        if (k >= n / 2) continue;

        // 计算 x 在第 k 对位置的数值，例如 "23" -> 23
        int currentVal = (x[2 * k] - '0') * 10 + (x[2 * k + 1] - '0');
        
        // 获取前一对的数字，用于确保相邻对不相同
        int prevDigit = -1;
        if (k > 0) {
            prevDigit = x[2 * k - 2] - '0';
        }

        // 我们需要找到一个数字 d，使得对子 dd 的值大于 currentVal
        // 且 d 不等于 prevDigit
        // 我们从 0 到 9 遍历寻找最小的满足条件的 d
        int foundD = -1;
        for (int d = 0; d <= 9; d++) {
            // 不能与前一对数字相同
            if (d == prevDigit) continue;
            
            // 构成的对子数值
            int pairVal = d * 10 + d;
            
            // 必须严格大于 x 在该位置的数值
            // 这样无论后面的位如何填充，整个数都会大于 x
            if (pairVal > currentVal) {
                foundD = d;
                break; // 找到了最小的可行 d，退出内层循环
            }
        }

        // 如果找到了合法的 d
        if (foundD != -1) {
            // 开始构造结果字符串
            // 首先复制前 k 对（即 x 的前 2*k 个字符）
            string res = x.substr(0, 2 * k);
            
            // 追加我们找到的更大的那一对
            res += (char)('0' + foundD);
            res += (char)('0' + foundD);
            
            // 剩下的位置（从 k+1 对开始到结束）全部填充最小的合法序列
            // 这样能保证构造出的数是基于当前拐点的最小数
            int lastD = foundD;
            for (int m = k + 1; m < n / 2; m++) {
                // 下一对的数字只能是 0 或 1（尽量小）
                // 只要不等于上一对的数字即可
                int nextD = (lastD == 0) ? 1 : 0;
                res += (char)('0' + nextD);
                res += (char)('0' + nextD);
                lastD = nextD; // 更新上一对数字
            }
            // 输出结果并结束程序
            cout << res << endl;
            return 0;
        }
        // 如果在当前 k 位置找不到合法的更大的对子，循环继续，回溯到 k-1 位置尝试
    }

    // 如果循环结束仍未找到（说明长度为 n 的双生数都比 x 小或者无法构造）
    // 则答案是长度为 n + 2 的最小双生数
    cout << getSmallest(n + 2) << endl;

    return 0;
}

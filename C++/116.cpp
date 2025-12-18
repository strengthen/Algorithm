#include <iostream>
#include <vector>
#include <string>

// 使用标准命名空间
using namespace std;

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    // 读取整数 n，表示排列的长度
    if (!(cin >> n)) return 0;

    string s;
    // 读取字符串 s，由 '0' 和 '1' 构成
    cin >> s;

    // 如果最后一个字符是 '0'，则无法构造满足条件的排列
    // 因为 s[n-1] 对应 s_n，若 s_n=0，则 p[1...n] 不能是排列，但这与题目要求 p 是排列矛盾
    if (s[n - 1] == '0') {
        cout << "-1" << endl;
        return 0;
    }

    // 用于存储构造的排列
    vector<int> p(n);
    // 记录上一个 '1' 的位置（1-based 索引），初始为 0
    int last_idx = 0;

    // 遍历字符串 s，注意 s 的下标从 0 开始，对应题目中的下标 i+1
    for (int i = 0; i < n; ++i) {
        // 当遇到 '1' 时，处理从 last_idx + 1 到 i + 1 的区间
        if (s[i] == '1') {
            // 当前 '1' 的位置（1-based）
            int current_idx = i + 1;
            
            // 区间长度
            int len = current_idx - last_idx;

            if (len == 1) {
                // 如果长度为 1，直接填入当前最大值 current_idx
                // 因为只有一个位置，必须填入该位置对应的值才能满足排列条件
                p[last_idx] = current_idx;
            } else {
                // 如果长度 > 1，说明中间有 '0'
                // 为了让中间的位置前缀不构成排列，我们采取贪心策略
                // 将当前区间最大的数 current_idx 放在区间的第一个位置
                // 这样该区间内除最后一个位置外，前缀最大值都会超过当前长度，从而不构成排列
                p[last_idx] = current_idx;
                
                // 剩下的位置依次填入 last_idx + 1 到 current_idx - 1
                int val = last_idx + 1;
                for (int j = last_idx + 1; j < current_idx; ++j) {
                    p[j] = val++;
                }
            }
            
            // 更新 last_idx 为当前位置，作为下一个区间的起点
            last_idx = current_idx;
        }
    }

    // 输出构造好的排列
    for (int i = 0; i < n; ++i) {
        // 输出当前元素
        cout << p[i];
        // 如果不是最后一个元素，输出空格
        if (i < n - 1) {
            cout << " ";
        }
    }
    // 输出换行符
    cout << endl;

    return 0;
}

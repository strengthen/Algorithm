#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

// HJ155 小A的线段（easy version）
// 题目要求：从 m 条线段中选择若干条，使得 1~n 每个整数点至少被覆盖 2 次。
// 数据范围：n <= 10^5, m <= 10。
// 因为 m 很小，可以利用状压（状态压缩）的思想。

int main() {
    // 优化输入输出效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    // 读取 n 和 m
    if (!(cin >> n >> m)) return 0;

    // 读取 m 条线段
    vector<pair<int, int>> segments(m);
    for (int i = 0; i < m; ++i) {
        cin >> segments[i].first >> segments[i].second;
    }

    // 使用差分数组记录每个点被哪些线段覆盖
    // diff[i] 是一个位掩码 (bitmask)，表示在点 i 处覆盖情况的变化
    // 第 j 位为 1 表示第 j 条线段覆盖了该点
    // 数组大小设为 n + 2 防止越界
    vector<int> diff(n + 2, 0);

    for (int i = 0; i < m; ++i) {
        int l = segments[i].first;
        int r = segments[i].second;
        
        // 利用异或操作进行差分更新
        // 进入线段区间 [l, r]，掩码异或上 (1 << i)
        diff[l] ^= (1 << i);
        // 离开线段区间，位置 r + 1，再次异或 (1 << i) 抵消影响
        diff[r + 1] ^= (1 << i);
    }

    // 存储所有出现的不同覆盖掩码
    // 因为 m <= 10，掩码范围 0 ~ 1023
    // 使用 has_mask 避免存储重复的掩码，减少后续计算量
    vector<int> unique_masks;
    vector<bool> has_mask(1 << m, false);
    
    int current_mask = 0;
    for (int i = 1; i <= n; ++i) {
        // 前缀异或和还原当前点的实际覆盖掩码
        current_mask ^= diff[i];
        
        // 如果该掩码是第一次出现，记录下来
        if (!has_mask[current_mask]) {
            has_mask[current_mask] = true;
            unique_masks.push_back(current_mask);
        }
    }

    long long ans = 0;
    int total_states = 1 << m; // 总的选法可能有 2^m 种

    // 枚举所有可能的线段选择方案
    // state 的二进制第 j 位为 1 表示选择了第 j 条线段
    for (int state = 0; state < total_states; ++state) {
        bool ok = true;
        
        // 对于当前选择方案 state，检查是否所有存在的点覆盖情况都满足条件
        for (int mask : unique_masks) {
            // mask 是某类点被所有 m 条线段覆盖的情况
            // state & mask 是这些点被“选中”的线段覆盖的情况
            // 我们需要选中的线段数 >= 2
            
            // 使用 bitset 计算二进制中 1 的个数
            if (bitset<10>(state & mask).count() < 2) {
                ok = false;
                break;
            }
        }
        
        // 如果所有点都满足覆盖数 >= 2，则该方案合法
        if (ok) {
            ans++;
        }
    }

    // 输出方案数对 998244353 取模的结果
    cout << ans % 998244353 << endl;

    return 0;
}

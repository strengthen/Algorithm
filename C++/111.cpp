#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// 解决气球谜题
int main() {
    // 优化IO速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // 读取气球数量
    if (!(cin >> n)) return 0;

    string s;
    // 读取气球初始颜色字符串
    cin >> s;

    vector<int> t(n);
    // 读取每个气球重新染色的时间
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    // prefix_sum[c][i] 表示前 i 个气球全部染成颜色 c 所需的总代价
    // c 的取值为 0, 1, 2，分别对应红、黄、蓝
    vector<vector<long long> > prefix_sum(3, vector<long long>(n + 1, 0));

    for (int i = 0; i < n; ++i) {
        // 当前气球的初始颜色
        int initial_color = s[i] - '0';
        for (int c = 0; c < 3; ++c) {
            // 如果目标颜色和初始颜色相同，代价为0，否则为t[i]
            long long cost = (initial_color == c) ? 0 : t[i];
            prefix_sum[c][i + 1] = prefix_sum[c][i] + cost;
        }
    }

    // 颜色的全排列，代表红黄蓝三种颜色块的相对顺序
    vector<int> p;
    p.push_back(0);
    p.push_back(1);
    p.push_back(2);
    long long min_total_cost = LLONG_MAX;

    // 遍历所有可能的颜色顺序 (例如: 0->1->2, 0->2->1, ...)
    do {
        int c1 = p[0];
        int c2 = p[1];
        int c3 = p[2];

        // 我们需要找到分割点 i 和 j (0 <= i <= j <= n)
        // 使得区间 [0, i) 染成 c1
        // 区间 [i, j) 染成 c2
        // 区间 [j, n) 染成 c3
        // 总代价 = (prefix_sum[c1][i] - prefix_sum[c1][0]) + 
        //          (prefix_sum[c2][j] - prefix_sum[c2][i]) + 
        //          (prefix_sum[c3][n] - prefix_sum[c3][j])
        // 整理公式得: (prefix_sum[c1][i] - prefix_sum[c2][i]) + (prefix_sum[c2][j] - prefix_sum[c3][j]) + prefix_sum[c3][n]

        long long current_perm_min_cost = LLONG_MAX;
        long long min_prev = LLONG_MAX; // 用于维护 min(prefix_sum[c1][i] - prefix_sum[c2][i])，其中 0 <= i <= j

        // 遍历 j 从 0 到 n
        // 对于每个 j，我们需要找到最佳的 i (0 <= i <= j)
        for (int j = 0; j <= n; ++j) {
            // 计算当前 i=j 时的 prefix_sum[c1][i] - prefix_sum[c2][i] 并尝试更新 min_prev
            // 注意这里 i 可以取 j，所以我们在处理 j 时先更新 i=j 的情况到 min_prev 中
            long long val_i = prefix_sum[c1][j] - prefix_sum[c2][j];
            if (val_i < min_prev) {
                min_prev = val_i;
            }

            // 计算当前 j 对应的最小代价
            // 此时 min_prev 已经是 min_{0<=i<=j} (prefix_sum[c1][i] - prefix_sum[c2][i])
            long long cost = min_prev + (prefix_sum[c2][j] - prefix_sum[c3][j]) + prefix_sum[c3][n];
            if (cost < current_perm_min_cost) {
                current_perm_min_cost = cost;
            }
        }

        if (current_perm_min_cost < min_total_cost) {
            min_total_cost = current_perm_min_cost;
        }

    } while (next_permutation(p.begin(), p.end()));

    // 输出最少需要的染色时间
    cout << min_total_cost << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 定义限制条件结构体
struct Constraint {
    int l, r;
    long long x, y, k;
    int id; // 原始索引（虽然本题不需要输出顺序，但保留是个好习惯）
};

// 按区间长度从小到大排序，如果长度相同，按左端点排序
bool compareConstraints(const Constraint& a, const Constraint& b) {
    if (a.r - a.l != b.r - b.l) {
        return (a.r - a.l) < (b.r - b.l);
    }
    return a.l < b.l;
}

// 构造满足特定0和1数量以及"01"子序列数量的字符串
// len: 字符串长度, x: 0的数量, y: 1的数量, k: 目标"01"子序列数量
string construct(int len, long long x, long long y, long long k) {
    string res = "";
    // 贪心策略：如果可以放'0'且放'0'后剩余的'01'数量仍能被满足，则放'0'
    // 实际上，如果当前剩余k >= y（当前剩余的1的数量），说明放一个0可以贡献y个逆序对（这里是01正序对）
    // 我们需要消耗k。放一个0，消耗y个k。
    // 如果 k >= y，我们通常应该放0吗？
    // 我们的目标是恰好凑齐k。
    // 如果我们放'0'，我们获得y个贡献。剩余需要 k-y。
    // 如果我们放'1'，我们获得0个贡献。剩余需要 k。
    
    // 正确的逻辑是：优先放0，只要放0后剩余的最大可能贡献足以覆盖剩余的k
    // 剩余x-1个0，y个1。最大贡献是 (x-1)*y。
    // 如果 (x-1)*y >= k - y，且 k >= y，我们可以放0。
    // 但是其实有一个更简单的逻辑：
    // 我们想要k尽可能小（如果k太大，我们必须放0在前面，因为0在前面贡献大）。
    // 反之，如果我们想要k大，0应该在前面。
    // 等等，0在前面贡献是y。0在后面贡献少。
    // 所以如果k比较大，我们要尽早放0。
    // 具体判断：
    // 当前还需要k。
    // 如果放'1'：剩余容量 x*(y-1)。如果 k <= x*(y-1)，说明放'1'是安全的，后面能凑齐。
    // 如果 k > x*(y-1)，说明放'1'会导致后面即使全放0在最前面也凑不齐k，所以必须放'0'。
    
    for (int i = 0; i < len; ++i) {
        if (x > 0) {
            // 尝试放'1'的条件：当前如果不放0（即放1），剩余的0和1（少一个1）能否凑出k
            // 放1不消耗k，但减少了未来0能贡献的y（因为y减少了）
            // 剩余 x 个 0, y-1 个 1。最大能产生的对数是 x * (y-1)。
            if (y > 0 && k <= x * (y - 1)) {
                res += '1';
                y--;
            } else {
                // 必须放0
                res += '0';
                x--;
                k -= y;
            }
        } else {
            res += '1';
            y--;
        }
    }
    return res;
}

int main() {
    // 优化IO速度
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Constraint> constraints(m);
    for (int i = 0; i < m; ++i) {
        cin >> constraints[i].l >> constraints[i].r >> constraints[i].x >> constraints[i].y >> constraints[i].k;
        constraints[i].id = i;
    }

    // 排序
    sort(constraints.begin(), constraints.end(), compareConstraints);

    // 最终结果字符串，初始化为'0'，长度为n+1 (1-based indexing)
    // 题目要求未覆盖部分可以任意，但通常填充0即可
    // 注意：题目中区间是1-based
    vector<char> ans(n + 1, '0');
    // 记录哪些位置已经被更小的区间覆盖了（虽然逻辑上我们只处理diff，但为了方便填充，我们需要标记）
    // 实际上我们不需要标记，因为我们是针对 diff 区间进行填充。
    // 我们只需要确切地知道 diff 区间的范围。
    
    // 处理第一个（最小的）区间
    {
        Constraint& cur = constraints[0];
        if (cur.x * cur.y < cur.k) {
            cout << -1 << endl;
            return 0;
        }
        string s = construct(cur.r - cur.l + 1, cur.x, cur.y, cur.k);
        for (int i = 0; i < s.length(); ++i) {
            ans[cur.l + i] = s[i];
        }
    }

    // 逐层处理后续区间
    for (int i = 1; i < m; ++i) {
        Constraint& cur = constraints[i];
        Constraint& prev = constraints[i-1];

        // 检查包含关系（题目保证，但作为防御性编程）
        // 实际上题目保证任意两个都是包含关系，且排序后 prev 一定被 cur 包含
        // 如果数据有误，这里可能会出问题，但我们假设数据符合描述
        
        long long x_diff = cur.x - prev.x;
        long long y_diff = cur.y - prev.y;
        
        if (x_diff < 0 || y_diff < 0) {
            cout << -1 << endl;
            return 0;
        }

        // 定义左差集区间和右差集区间
        // prev: [prev.l, prev.r]
        // cur: [cur.l, cur.r]
        // L_diff: [cur.l, prev.l - 1]
        // R_diff: [prev.r + 1, cur.r]
        
        int len_L = prev.l - cur.l;
        int len_R = cur.r - prev.r;
        
        // 我们需要找到 x_L (左区间的0的数量)，使得满足k的限制
        // x_L 的范围
        // x_L <= len_L
        // x_L <= x_diff
        // x_R = x_diff - x_L <= len_R  =>  x_L >= x_diff - len_R
        // x_L >= 0
        
        long long min_xL = max(0LL, x_diff - len_R);
        long long max_xL = min((long long)len_L, x_diff);
        
        bool found = false;
        long long best_xL = -1;
        long long best_kL = -1, best_kR = -1;

        // 遍历所有可能的 x_L
        for (long long xL = min_xL; xL <= max_xL; ++xL) {
            long long xR = x_diff - xL;
            long long yL = len_L - xL;
            long long yR = len_R - xR;
            
            // 计算需要的 k_diff (来自 L_diff 和 R_diff 内部的 k 之和)
            // k_cur = k_prev + k_L + k_R + cross_terms
            // cross_terms = (0 in L, 1 in prev) + (0 in L, 1 in R) + (0 in prev, 1 in R)
            long long cross_terms = xL * prev.y + xL * yR + prev.x * yR;
            long long k_needed = cur.k - prev.k - cross_terms;
            
            // 检查 k_needed 是否合法
            // k_L 最大为 xL * yL, 最小为 0
            // k_R 最大为 xR * yR, 最小为 0
            long long max_k_capacity = xL * yL + xR * yR;
            
            if (k_needed >= 0 && k_needed <= max_k_capacity) {
                found = true;
                best_xL = xL;
                
                // 分配 k_needed 给 k_L 和 k_R
                // 贪心地给 k_L 分配
                best_kL = min(k_needed, xL * yL);
                best_kR = k_needed - best_kL;
                break;
            }
        }

        if (!found) {
            cout << -1 << endl;
            return 0;
        }

        // 填充 L_diff
        if (len_L > 0) {
            long long yL = len_L - best_xL;
            string sL = construct(len_L, best_xL, yL, best_kL);
            for (int k = 0; k < len_L; ++k) {
                ans[cur.l + k] = sL[k];
            }
        }
        
        // 填充 R_diff
        if (len_R > 0) {
            long long xR = x_diff - best_xL;
            long long yR = len_R - xR;
            string sR = construct(len_R, xR, yR, best_kR);
            for (int k = 0; k < len_R; ++k) {
                ans[prev.r + 1 + k] = sR[k];
            }
        }
    }

    // 输出结果 (忽略索引0)
    for (int i = 1; i <= n; ++i) {
        cout << ans[i];
    }
    cout << endl;

    return 0;
}

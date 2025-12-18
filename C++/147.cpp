#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 定义无穷大，用于初始化最小值
// Define infinity for long long
const long long INF = 4e18; 

// 线段树结构体，支持单点更新和区间查询最小值
// Segment Tree to support point update and range minimum query
struct SegTree {
    int n;
    vector<long long> tree;

    // 构造函数，初始化线段树
    SegTree(int size) {
        n = size;
        // 4倍大小足以容纳线段树节点
        tree.assign(4 * n, INF);
    }

    // 更新函数
    void update(int node, int start, int end, int idx, long long val) {
        if (start == end) {
            // 取当前位置的最小值（应对重复值的情况）
            tree[node] = min(tree[node], val); 
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);
        // 更新当前节点为左右子节点的最小值
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    // 查询函数
    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l)
            return INF;
        if (l <= start && end <= r)
            return tree[node];
        int mid = (start + end) / 2;
        return min(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }

    // 辅助函数：更新
    void update(int idx, long long val) {
        update(1, 1, n, idx, val);
    }

    // 辅助函数：查询
    long long query(int l, int r) {
        if (l > r) return INF;
        return query(1, 1, n, l, r);
    }
};

int main() {
    // 优化输入输出效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> A(n);
    vector<long long> sortedA;
    // 读取输入数据
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
        sortedA.push_back(A[i]);
    }

    // 离散化处理：排序并去重
    sort(sortedA.begin(), sortedA.end());
    sortedA.erase(unique(sortedA.begin(), sortedA.end()), sortedA.end());
    
    // 获取排名的lambda函数
    auto get_rank = [&](long long val) {
        // lower_bound返回第一个大于等于val的迭代器，减去begin得到索引，+1得到1-based排名
        return lower_bound(sortedA.begin(), sortedA.end(), val) - sortedA.begin() + 1;
    };

    int m = sortedA.size();
    // tree1用于处理 A[j] <= A[i] 的情况：存储 min(j^2 + A[j]^2)
    SegTree tree1(m); 
    // tree2用于处理 A[j] > A[i] 的情况：存储 min(j^2 - A[j]^2)
    SegTree tree2(m); 

    long long max_dist = 0;

    // 遍历每一个元素作为 i (当前元素)，并在之前的元素中寻找最佳 j
    for (int i = 1; i <= n; ++i) { // i 使用 1-based 索引
        long long val = A[i - 1];
        long long i_sq = (long long)i * i;
        long long val_sq = val * val;
        int r = get_rank(val);

        // 情况 1: A[j] <= A[i]
        // 目标: maximize (i^2 + A[i]^2) - (j^2 + A[j]^2)
        // 等价于: minimize (j^2 + A[j]^2)
        // 在 [1, r] 范围内查询最小值
        long long min_val1 = tree1.query(1, r);
        if (min_val1 != INF) {
            max_dist = max(max_dist, (i_sq + val_sq) - min_val1);
        }

        // 情况 2: A[j] > A[i]
        // 目标: maximize (i^2 - A[i]^2) - (j^2 - A[j]^2)
        // 等价于: minimize (j^2 - A[j]^2)
        // 在 [r + 1, m] 范围内查询最小值
        long long min_val2 = tree2.query(r + 1, m);
        if (min_val2 != INF) {
            max_dist = max(max_dist, (i_sq - val_sq) - min_val2);
        }

        // 将当前 i 的信息更新到线段树中，供后续元素作为 j 查询
        tree1.update(r, i_sq + val_sq);
        tree2.update(r, i_sq - val_sq);
    }

    cout << max_dist << endl;

    return 0;
}

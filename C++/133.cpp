#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// 并查集结构体，用于管理集合的合并和查找
struct DSU {
    vector<int> parent; // 存储每个节点的父节点
    vector<int> size;   // 存储以每个节点为根的集合大小

    // 构造函数，初始化并查集
    DSU(int n) {
        parent.resize(n);
        // 初始化父节点为自身
        iota(parent.begin(), parent.end(), 0);
        // 初始化每个集合大小为1
        size.assign(n, 1);
    }

    // 查找操作，带路径压缩
    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]); // 路径压缩，直接指向根节点
    }

    // 合并操作，按秩合并（按大小合并）
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            // 将小集合合并到大集合，保持树的高度较小
            if (size[rootX] < size[rootY]) swap(rootX, rootY);
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
};

// 处理单组测试数据的函数
void solve() {
    int n;
    if (!(cin >> n)) return; // 读取账号数量

    vector<long long> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i]; // 读取每个账号的权重
    }

    DSU dsu(n); // 创建包含n个元素的并查集
    
    // last_seen[j] 存储上一个第 j 位为 1 的账号索引
    // 64位足够覆盖 10^18 (2^60 > 10^18)
    vector<int> last_seen(64, -1); 

    for (int i = 0; i < n; ++i) {
        // 遍历权重的每一位（0到62位）
        for (int j = 0; j < 63; ++j) {
            // 检查 w[i] 的第 j 位是否为 1
            if ((w[i] >> j) & 1) {
                // 如果之前有账号的第 j 位也是 1，则将当前账号与该账号合并
                if (last_seen[j] != -1) {
                    dsu.unite(i, last_seen[j]);
                }
                // 更新第 j 位最后出现的账号索引为当前账号
                last_seen[j] = i;
            }
        }
    }

    int max_size = 0;
    // 遍历所有账号，找到最大的集合大小
    for (int i = 0; i < n; ++i) {
        // 只检查根节点，避免重复计数
        if (dsu.parent[i] == i) {
            max_size = max(max_size, dsu.size[i]);
        }
    }
    cout << max_size << endl; // 输出结果
}

int main() {
    // 优化输入输出效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) { // 读取测试组数
        while (t--) {
            solve();
        }
    }
    return 0;
}

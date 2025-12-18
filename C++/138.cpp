// 138.cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义模数
const long long MOD = 1e9 + 7;
// 定义无穷大
const long long INF = 1e18;

// 定义状态结果结构体
struct Result {
    long long cost;   // 最小代价
    long long count;  // 方案数
};

// 更新函数，保留最小代价，相同代价累加方案数
void update(Result& target, long long cost, long long count) {
    if (cost < target.cost) {
        target.cost = cost;
        target.count = count;
    } else if (cost == target.cost) {
        target.count = (target.count + count) % MOD;
    }
}

int n, k;
bool is_marked[100005]; // 标记数组
vector<int> adj[100005]; // 邻接表
Result dp[100005][2]; 
// dp[u][0]: u所在的连通分量已经连接到未标记点（满足条件）
// dp[u][1]: u所在的连通分量全是标记点，且尚未连接到未标记点（不满足条件，需要向上传递）

void dfs(int u, int p) {
    // 初始化叶子节点状态
    if (is_marked[u]) {
        // 如果u是标记点
        dp[u][0] = Result{INF, 0}; // 暂时没有连接到未标记点
        dp[u][1] = Result{0, 1};   // 自身是标记点，代价0，方案1
    } else {
        // 如果u是未标记点
        dp[u][0] = Result{0, 1};   // 自身就是未标记点，满足条件
        dp[u][1] = Result{INF, 0}; // 不可能处于“未连接到未标记点”的状态
    }

    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);

        Result next_dp[2];
        next_dp[0] = Result{INF, 0};
        next_dp[1] = Result{INF, 0};

        // 判断是否是自动红边（两端都是标记点）
        bool automatic = is_marked[u] && is_marked[v];

        // 状态转移
        // 枚举u的当前状态i和子节点v的状态j
        for (int i = 0; i < 2; ++i) {
            if (dp[u][i].cost == INF) continue;
            for (int j = 0; j < 2; ++j) {
                if (dp[v][j].cost == INF) continue;

                if (automatic) {
                    // 自动红边，代价为0，强制连接
                    // 只要有一端满足条件(0)，合并后就满足条件(0)
                    // 否则合并后仍不满足(1)
                    int new_state = (i == 0 || j == 0) ? 0 : 1;
                    long long new_cost = dp[u][i].cost + dp[v][j].cost;
                    long long new_count = (dp[u][i].count * dp[v][j].count) % MOD;
                    update(next_dp[new_state], new_cost, new_count);
                } else {
                    // 手动边，代价为1
                    
                    // 选项1: 不染色 (Cut)，代价0
                    // 要求子节点v必须已经自我满足(状态0)，否则v所在的连通块会孤立无法满足
                    if (j == 0) {
                        // u的状态保持不变
                        long long new_cost = dp[u][i].cost + dp[v][j].cost;
                        long long new_count = (dp[u][i].count * dp[v][j].count) % MOD;
                        update(next_dp[i], new_cost, new_count);
                    }

                    // 选项2: 染色 (Color)，代价1
                    // 相当于连接了u和v，逻辑同自动红边
                    int new_state = (i == 0 || j == 0) ? 0 : 1;
                    long long new_cost = dp[u][i].cost + dp[v][j].cost + 1;
                    long long new_count = (dp[u][i].count * dp[v][j].count) % MOD;
                    update(next_dp[new_state], new_cost, new_count);
                }
            }
        }
        // 更新u的状态
        dp[u][0] = next_dp[0];
        dp[u][1] = next_dp[1];
    }
}

int main() {
    // 加速IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> k)) return 0;

    for (int i = 0; i < k; ++i) {
        int val;
        cin >> val;
        is_marked[val] = true;
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    // 最终答案是dp[1][0]
    // dp[1][1]代表根节点所在的标记连通块没有连接到未标记点，这是不合法的
    cout << dp[1][0].cost << " " << dp[1][0].count << endl;

    return 0;
}

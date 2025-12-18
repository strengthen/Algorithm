#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// 定义常量，最大英雄数量和最大cost
// Define constants for maximum number of heroes and max cost
const int MAX_N = 1005;
const int MAX_C = 1005;

// 定义英雄结构体
// Define Hero structure
struct Hero {
    int id;
    int cost;
    long long power;
};

// 定义双生关系结构体
// Define Twin pair structure
struct PairInfo {
    int u, v;
    long long bonus;
};

int main() {
    // 优化输入输出效率
    // Optimize I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, C, m;
    // 读取英雄数量，最大cost限制，双生对数
    // Read number of heroes, max cost limit, and number of twin pairs
    if (!(cin >> n >> C >> m)) return 0;

    // 存储所有英雄的信息，下标从1开始
    // Store information for all heroes, 1-based index
    vector<Hero> heroes(n + 1);
    for (int i = 1; i <= n; ++i) {
        heroes[i].id = i;
        cin >> heroes[i].cost >> heroes[i].power;
    }

    // 记录双生关系
    // Record twin relationships
    // pair_map用于快速查找某个英雄是否在双生关系中以及对应的关系索引
    // pair_map stores the relationship index for a hero if they are in a pair
    map<int, int> hero_to_pair_index;
    vector<PairInfo> pairs(m);
    for (int i = 0; i < m; ++i) {
        cin >> pairs[i].u >> pairs[i].v >> pairs[i].bonus;
        hero_to_pair_index[pairs[i].u] = i;
        hero_to_pair_index[pairs[i].v] = i;
    }

    // dp[k][j] 表示选择了 k 个英雄，总 cost 为 j 时的最大战斗力
    // dp[k][j] represents max power with k heroes and total cost j
    // 初始化为 -1 表示不可达
    // Initialize with -1 to indicate unreachable states
    vector<vector<long long>> dp(5, vector<long long>(C + 1, -1));
    
    // 初始状态：选0个英雄，cost为0，战斗力为0
    // Initial state: 0 heroes, 0 cost, 0 power
    dp[0][0] = 0;

    // 标记英雄是否已经处理过
    // Mark if a hero has been processed
    vector<bool> processed(n + 1, false);

    // 首先处理所有的双生对
    // First process all twin pairs
    for (int i = 0; i < m; ++i) {
        int u = pairs[i].u;
        int v = pairs[i].v;
        long long w = pairs[i].bonus;
        
        // 标记这两个英雄已处理
        // Mark these two heroes as processed
        processed[u] = true;
        processed[v] = true;

        // 这是一个分组背包问题，这组（一对双生英雄）有三种选择策略（互斥）：
        // This is a grouped knapsack problem. For this group (pair), there are 3 mutually exclusive choices:
        // 1. 只选 u (Select only u)
        // 2. 只选 v (Select only v)
        // 3. 选 u 和 v (Select both u and v)
        // 注意：都不选的情况隐含在DP的继承中
        // Note: The "select neither" case is implied by carrying over previous DP states

        // 必须使用临时DP数组或者倒序遍历以避免同组内多次选择
        // Must use a temporary DP array to avoid selecting multiple times from the same group in one step
        vector<vector<long long>> next_dp = dp;

        // 获取英雄的具体属性
        // Get hero attributes
        int cost_u = heroes[u].cost;
        long long power_u = heroes[u].power;
        int cost_v = heroes[v].cost;
        long long power_v = heroes[v].power;
        int cost_both = cost_u + cost_v;
        long long power_both = power_u + power_v + w;

        // 遍历当前已选英雄数量 k (从0到3，因为最多选4个)
        // Iterate through current number of selected heroes k (0 to 3, as max is 4)
        for (int k = 0; k < 4; ++k) {
            // 遍历当前 cost j
            // Iterate through current cost j
            for (int j = 0; j <= C; ++j) {
                if (dp[k][j] == -1) continue; // 如果当前状态不可达，跳过 (If state unreachable, skip)

                // 选项 1: 只选 u
                // Option 1: Select only u
                if (k + 1 <= 4 && j + cost_u <= C) {
                    next_dp[k + 1][j + cost_u] = max(next_dp[k + 1][j + cost_u], dp[k][j] + power_u);
                }

                // 选项 2: 只选 v
                // Option 2: Select only v
                if (k + 1 <= 4 && j + cost_v <= C) {
                    next_dp[k + 1][j + cost_v] = max(next_dp[k + 1][j + cost_v], dp[k][j] + power_v);
                }

                // 选项 3: 同时选 u 和 v
                // Option 3: Select both u and v
                if (k + 2 <= 4 && j + cost_both <= C) {
                    next_dp[k + 2][j + cost_both] = max(next_dp[k + 2][j + cost_both], dp[k][j] + power_both);
                }
            }
        }
        // 更新DP表
        // Update DP table
        dp = next_dp;
    }

    // 处理剩下的单体英雄
    // Process remaining single heroes
    for (int i = 1; i <= n; ++i) {
        if (processed[i]) continue; // 如果是双生英雄已经处理过，跳过 (If processed as twin, skip)

        int cost = heroes[i].cost;
        long long power = heroes[i].power;
        
        // 0-1 背包，需要倒序遍历或者使用临时数组
        // 0-1 Knapsack, need reverse iteration or temporary array
        // 这里为了统一逻辑清晰，继续使用临时数组（虽然倒序也可以）
        // For clarity, using temporary array (though reverse iteration works too)
        vector<vector<long long>> next_dp = dp;

        for (int k = 0; k < 4; ++k) {
            for (int j = 0; j <= C; ++j) {
                if (dp[k][j] == -1) continue;

                // 选这个英雄
                // Select this hero
                if (k + 1 <= 4 && j + cost <= C) {
                    next_dp[k + 1][j + cost] = max(next_dp[k + 1][j + cost], dp[k][j] + power);
                }
            }
        }
        dp = next_dp;
    }

    // 寻找最大值
    // Find the maximum value
    long long max_power = 0;
    for (int k = 0; k <= 4; ++k) {
        for (int j = 0; j <= C; ++j) {
            max_power = max(max_power, dp[k][j]);
        }
    }

    // 输出结果
    // Output result
    cout << max_power << endl;

    return 0;
}

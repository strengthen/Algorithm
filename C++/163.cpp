#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// 定义最大资源值范围，题目中为 [10, 300]
const int MAX_VAL = 300;
const int MIN_VAL = 10;
// 距离数组，存储从初始值 10 到各个目标值的最少操作次数
// 范围是 [10, 300]，数组大小开大一点防止越界
int dist[MAX_VAL + 5];

// 检查数值是否在合法范围内 [10, 300]
bool isValid(int x) {
    return x >= MIN_VAL && x <= MAX_VAL;
}

// 广度优先搜索 (BFS) 预处理最短路径
// 计算从起点 10 到达区间 [10, 300] 内任意一点的最少步数
void bfs() {
    // 初始化距离数组为 -1，表示未访问
    memset(dist, -1, sizeof(dist));
    queue<int> q;

    // 起点是 10，步数为 0
    dist[10] = 0;
    q.push(10);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // 定义所有可能的操作变化量
        // 操作：+1, -1, +10, -10, +100, -100
        int deltas[] = {1, -1, 10, -10, 100, -100};
        
        // 尝试加减操作
        for (int d : deltas) {
            int v = u + d;
            // 题目要求资源总量始终保持在区间 [10, 300]
            if (isValid(v)) {
                if (dist[v] == -1) { // 如果未访问过，说明找到了到 v 的最短路径
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        // 尝试特殊操作：直接设为 10
        // 虽然起点就是 10，但理论上可以从其他点跳回 10 (虽然不会是最优解的起手式，但作为图的边是存在的)
        int v_min = 10;
        if (isValid(v_min) && dist[v_min] == -1) {
             dist[v_min] = dist[u] + 1;
             q.push(v_min);
        }

        // 尝试特殊操作：直接设为 300
        int v_max = 300;
        if (isValid(v_max) && dist[v_max] == -1) {
             dist[v_max] = dist[u] + 1;
             q.push(v_max);
        }
    }
}

int main() {
    // 优化 I/O 操作，提高大量数据输入输出的效率
    // 因为 T 最大可达 10^5，这一步很重要
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 预处理所有可能目标值的最小步数
    bfs();

    int T;
    // 读取测试组数
    if (cin >> T) {
        while (T--) {
            int a, b, c, d;
            // 读取每组的 4 个目标资源值
            cin >> a >> b >> c >> d;
            
            // 四种资源的操作是相互独立的
            // 初始值都是 10
            // 总最少操作次数 = 4 种资源分别到达目标值所需的最少操作次数之和
            // 由于 a, b, c, d 都在 [10, 300] 范围内，直接查表即可
            long long ans = (long long)dist[a] + dist[b] + dist[c] + dist[d];
            
            cout << ans << "\n";
        }
    }
    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 定义状态结构体，包含当前坐标、当前余数和步数
struct State {
    int x;
    int y;
    int rem; // 当前计数器值除以 (p-1) 的余数
    int step;
};

// 方向数组：上、下、左、右
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main() {
    // 优化输入输出
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, p;
    if (!(cin >> n >> m >> p)) return 0;

    // 题目要求的模数是 p-1
    int mod_val = p - 1;

    // 读取矩阵 a
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    // 读取矩阵 b (虽然在这个特定的取模性质下用不到 b，但需要消耗输入流)
    // 根据欧拉定理或简单的模运算性质，p^k % (p-1) == 1，只要 k >= 0
    // c_{i,j} = a_{i,j} * p^(2^b_{i,j})
    // c_{i,j} % (p-1) = (a_{i,j} % (p-1)) * (1 % (p-1)) = a_{i,j} % (p-1)
    int temp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> temp;
        }
    }

    // 访问标记数组：visited[x][y][remainder]
    // p 最大 10^4，所以余数范围 0 到 9999
    // 使用 vector 动态分配以避免栈溢出（虽然 10*10*10000 不大，但在 main 中分配更安全）
    vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(p, false)));

    queue<State> q;

    // 初始状态
    // 初始计数器为 c_{1,1}，即 a[0][0]
    // 注意：如果 p=2, mod_val=1, 任何数 % 1 都是 0。 a[0][0] % 1 = 0
    int start_rem = 0;
    if (mod_val > 0) {
        start_rem = a[0][0] % mod_val;
    } else {
        // 理论上 p >= 2，所以 mod_val >= 1。这里是为了防御性编程。
        start_rem = 0;
    }
    
    q.push({0, 0, start_rem, 0});
    visited[0][0][start_rem] = true;

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        // 检查是否到达出口 (n-1, m-1) 且计数器满足条件
        if (current.x == n - 1 && current.y == m - 1 && current.rem == 0) {
            cout << current.step << endl;
            return 0;
        }

        // 尝试四个方向移动
        for (int i = 0; i < 4; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            // 检查边界
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                // 计算新的余数
                int new_rem = 0;
                if (mod_val > 0) {
                    new_rem = (current.rem + a[nx][ny]) % mod_val;
                }
                
                // 如果该状态未访问过，则加入队列
                if (!visited[nx][ny][new_rem]) {
                    visited[nx][ny][new_rem] = true;
                    q.push({nx, ny, new_rem, current.step + 1});
                }
            }
        }
    }

    // 无法逃离
    cout << "-1" << endl;

    return 0;
}

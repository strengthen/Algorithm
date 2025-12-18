#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;

// 定义无穷大
const int INF = 1e9;
// 方向数组：上、下、左、右
int dx[] = {-1, 1, 0, 0}; 
int dy[] = {0, 0, -1, 1}; 

int main() {
    // 提高IO效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, start_x, start_y;
    // 读取输入
    if (!(cin >> n >> m >> start_x >> start_y)) return 0;

    // 转换为0-based索引
    --start_x;
    --start_y;

    vector<string> grid(n);
    vector<pair<int, int>> portals;
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            // 记录所有传送门位置
            if (grid[i][j] == '@') {
                portals.push_back({i, j});
            }
        }
    }

    // BFS 1: 计算任意点到最近传送门的最短距离（用于单人模式）
    // dist_solo[i][j] 存储从 (i, j) 到最近 '@' 的步数
    vector<vector<int>> dist_solo(n, vector<int>(m, INF));
    queue<pair<int, int>> q_solo;

    // 将所有传送门加入队列作为起点
    for (const auto& p : portals) {
        dist_solo[p.first][p.second] = 0;
        q_solo.push(p);
    }

    // 多源BFS计算单人逃生距离
    while (!q_solo.empty()) {
        auto [r, c] = q_solo.front();
        q_solo.pop();

        for (int k = 0; k < 4; ++k) {
            int nr = r + dx[k];
            int nc = c + dy[k];

            // 只能走平地或传送门（其实传送门距离为0，不会被更新）
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] != '#') {
                if (dist_solo[nr][nc] == INF) {
                    dist_solo[nr][nc] = dist_solo[r][c] + 1;
                    q_solo.push({nr, nc});
                }
            }
        }
    }

    // BFS 2: 双人同时移动模式
    // dist_sim[i][j] 存储玩家A位于(i, j)时的步数（此时玩家B的位置是固定的对称点）
    vector<vector<int>> dist_sim(n, vector<int>(m, INF));
    queue<pair<int, int>> q_sim;

    // 初始状态
    dist_sim[start_x][start_y] = 0;
    q_sim.push({start_x, start_y});

    int min_total_steps = INF;

    while (!q_sim.empty()) {
        auto [r1, c1] = q_sim.front();
        q_sim.pop();

        int cur_dist = dist_sim[r1][c1];
        
        // 计算玩家B的位置
        // r1 + r2 = 2 * start_x  => r2 = 2 * start_x - r1
        // c1 + c2 = 2 * start_y  => c2 = 2 * start_y - c1
        int r2 = 2 * start_x - r1;
        int c2 = 2 * start_y - c1;
        
        // 尝试玩家A的4个移动方向
        for (int k = 0; k < 4; ++k) {
            // 玩家A移动
            int nr1 = r1 + dx[k];
            int nc1 = c1 + dy[k];
            
            // 玩家B向相反方向移动
            // 0(U)<->1(D), 2(L)<->3(R)
            int k2;
            if (k == 0) k2 = 1;
            else if (k == 1) k2 = 0;
            else if (k == 2) k2 = 3;
            else k2 = 2;
            
            int nr2 = r2 + dx[k2];
            int nc2 = c2 + dy[k2];
            
            // 检查边界
            if (nr1 < 0 || nr1 >= n || nc1 < 0 || nc1 >= m ||
                nr2 < 0 || nr2 >= n || nc2 < 0 || nc2 >= m) {
                continue;
            }
            
            // 检查陷阱
            if (grid[nr1][nc1] == '#' || grid[nr2][nc2] == '#') {
                continue;
            }
            
            // 检查传送门
            bool p1 = (grid[nr1][nc1] == '@');
            bool p2 = (grid[nr2][nc2] == '@');
            
            if (p1 && p2) {
                // 两人同时离开
                min_total_steps = min(min_total_steps, cur_dist + 1);
            } else if (p1) {
                // A离开，B继续单人模式
                if (dist_solo[nr2][nc2] != INF) {
                    min_total_steps = min(min_total_steps, cur_dist + 1 + dist_solo[nr2][nc2]);
                }
            } else if (p2) {
                // B离开，A继续单人模式
                if (dist_solo[nr1][nc1] != INF) {
                    min_total_steps = min(min_total_steps, cur_dist + 1 + dist_solo[nr1][nc1]);
                }
            } else {
                // 都没离开，继续双人模式
                if (dist_sim[nr1][nc1] == INF) {
                    dist_sim[nr1][nc1] = cur_dist + 1;
                    q_sim.push({nr1, nc1});
                }
            }
        }
    }

    // 输出结果
    if (min_total_steps == INF) {
        cout << -1 << endl;
    } else {
        cout << min_total_steps << endl;
    }

    return 0;
}

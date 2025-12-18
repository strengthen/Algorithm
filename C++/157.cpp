#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

// 定义坐标点结构体，用于BFS搜索
// Define coordinate point structure for BFS search
struct Point {
    int r, c;
};

int main() {
    // 优化C++标准流的I/O效率
    // Optimize I/O efficiency for C++ standard streams
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    // 读取行数n和列数m
    // Read number of rows n and columns m
    if (!(cin >> n >> m)) return 0;

    // 使用vector存储网格地图
    // Use vector to store the grid map
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        // 读取每一行字符串
        // Read each row string
        cin >> grid[i];
    }

    // 标记数组，记录位置是否已访问，初始化为false
    // Visited array to record if a position has been visited, initialized to false
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    // 记录长方形图案的数量
    // Record the number of rectangular patterns
    int rectangleCount = 0;

    // 定义四个方向的偏移量（上、下、左、右）
    // Define offsets for four directions (up, down, left, right)
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // 遍历整个网格
    // Iterate through the entire grid
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // 如果遇到未访问的'.'，说明是一个新的连通块（剪下的图案）
            // If an unvisited '.' is encountered, it indicates a new connected component (cut-out pattern)
            if (grid[i][j] == '.' && !visited[i][j]) {
                // 初始化当前连通块的边界和点数
                // Initialize boundaries and point count for the current component
                int min_r = i, max_r = i;
                int min_c = j, max_c = j;
                int count = 0;

                // 使用队列进行广度优先搜索(BFS)
                // Use queue for Breadth-First Search (BFS)
                queue<Point> q;
                q.push({i, j});
                visited[i][j] = true;

                while (!q.empty()) {
                    Point curr = q.front();
                    q.pop();
                    count++;

                    // 更新连通块的最小/最大行号和列号
                    // Update min/max row and column indices for the component
                    min_r = min(min_r, curr.r);
                    max_r = max(max_r, curr.r);
                    min_c = min(min_c, curr.c);
                    max_c = max(max_c, curr.c);

                    // 检查当前点的四个相邻方向
                    // Check four adjacent directions of the current point
                    for (int k = 0; k < 4; ++k) {
                        int nr = curr.r + dr[k];
                        int nc = curr.c + dc[k];

                        // 检查边界条件
                        // Check boundary conditions
                        if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                            // 如果相邻点是'.'且未被访问，加入队列
                            // If the adjacent point is '.' and not visited, add to queue
                            if (grid[nr][nc] == '.' && !visited[nr][nc]) {
                                visited[nr][nc] = true;
                                q.push({nr, nc});
                            }
                        }
                    }
                }

                // 判断该连通块是否为长方形
                // Check if the connected component is a rectangle
                // 如果点数等于(最大行-最小行+1) * (最大列-最小列+1)，则为实心长方形
                // If point count equals (max_row - min_row + 1) * (max_col - min_col + 1), it is a solid rectangle
                long long width = max_c - min_c + 1;
                long long height = max_r - min_r + 1;
                if (count == width * height) {
                    rectangleCount++;
                }
            }
        }
    }

    // 输出结果
    // Output the result
    cout << rectangleCount << endl;

    return 0;
}
